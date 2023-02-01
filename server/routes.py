from server import app, posts, datetime, json
from flask import render_template, url_for, request, send_file


@app.route("/", methods=["GET"])
def home():
    return render_template('home.html', posts=posts)


@app.route("/get", methods=["GET"])
def get_request():
    new_get = dict()
    new_get['date'] = datetime.datetime.now().ctime()
    new_get['title'] = "Get Request has been received"
    new_get['path'] = "http://localhost:5000/get"
    new_get['body'] = ''
    posts.append(new_get)

    with open("db.json", "w") as db_file:
        json.dump(posts, db_file)

    return render_template('neverssl.html')


@app.route("/get_params", methods=["GET"])
def get_params():
    new_get = dict()
    new_get['date'] = datetime.datetime.now().ctime()
    new_get['title'] = "Get Request with parameters has been received"
    new_get['path'] = "http://localhost:5000/get_params"
    new_get['body'] = ''
    new_get['params'] = {k: v for k, v in request.args.items()}
    posts.append(new_get)

    with open("db.json", "w") as db_file:
        json.dump(posts, db_file)

    return render_template('home.html', posts=posts)


@app.route("/life_cycle", methods=["POST"])
def life_cycle():
    new_post = dict()
    new_post['date'] = datetime.datetime.now().ctime()
    new_post['title'] = "POST Request has been received"
    new_post['path'] = "http://localhost:5000/life_cycle"
    new_post['params'] = {k: v for k, v in request.args.items()}
    new_post['body'] = request.data.decode()

    if request.headers.get('Content-Length') is not None:
        new_post['c_len'] = request.headers['Content-Length']

    posts.append(new_post)

    with open("db.json", "w") as db_file:
        json.dump(posts, db_file)

    return render_template('sample.html')


@app.route("/pdf", methods=["GET"])
def pdf():
    new_get = dict()
    new_get['date'] = datetime.datetime.now().ctime()
    new_get['title'] = "Get Request has been received"
    new_get['path'] = "http://localhost:5000/pdf"
    new_get['body'] = ''
    posts.append(new_get)

    with open("db.json", "w") as db_file:
        json.dump(posts, db_file)

    return send_file('templates/pdf.pdf', download_name="pdf.pdf")


@app.route("/post", methods=["POST"])
def post_request():
    new_post = dict()
    new_post['date'] = datetime.datetime.now().ctime()
    new_post['title'] = "Post Request has been received"
    new_post['path'] = "http://localhost:5000/post"
    new_post['body'] = request.data.decode('utf-8')

    if request.headers.get('Content-Length') is not None:
        new_post['c_len'] = request.headers['Content-Length']

    posts.append(new_post)

    with open("db.json", "w") as db_file:
        json.dump(posts, db_file)

    return render_template('home.html', posts=posts)


@app.route("/delete_wall", methods=["DELETE"])
def delete_wall():
    posts.clear()
    posts.append(
        {
            "date": datetime.datetime.now().ctime(),
            "title": "Requests Wall",
            "path": "#",
            "body": ""
        }
    )

    with open("db.json", "w") as db_file:
        json.dump(posts, db_file)

    return render_template('home.html', posts=posts)


@app.route('/puzzle', methods=["GET"])
def puzzle():
    params = request.args
    if all(p is True for p in params.values()):
        puz = '''
        Cross-Site Scripting (XSS) attacks are a type of injection, in which malicious scripts are injected
        into otherwise benign and trusted websites. XSS attacks occur when an attacker uses a web
        application
        to send malicious code, generally in the form of a browser side script, to a different end user.
        Flaws that allow these attacks to succeed are quite widespread and occur anywhere a web application
        uses input from a user within the output it generates without validating or encoding it.

        An attacker can use XSS to send a malicious script to an unsuspecting user.
        The end user’s browser has no way to know that the script should not be trusted,
        and will execute the script. Because it thinks the script came from a trusted source,
        the malicious script can access any cookies, session tokens,
        or other sensitive information retained by the browser and used with that site.
        These scripts can even rewrite the content of the HTML page.

        Can you come up with a simple way to compromise EX2 server to execute additional code?
        '''

        posts.append(
            {
                "puzzle": puz
            }
        )

    return render_template('home.html', value=posts)
