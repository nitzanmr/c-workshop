from flask import Flask
import datetime
import json

app = Flask(__name__)

posts = [
    {
        "date": datetime.datetime.now().ctime(),
        "title": "Requests Wall",
        "path": "#",
        "body": ""
    }
]

with open("db.json", "w") as db_file:
    json.dump(posts, db_file)

from server import routes
