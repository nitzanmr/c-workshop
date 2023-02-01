import subprocess
import os
import json

import requests
from prettytable import PrettyTable


EXECUTABLE = "ex2"
C_FILES = "*.c"
SERVER_PROC = None


def check_leaks():
    leaks = True
    with open("valgrind-log.txt", 'r') as valgrind_log:
        try:

            val_lines = valgrind_log.readlines()

        except UnicodeDecodeError:
            return False

        for line in val_lines:
            if "no leaks are possible" in line:
                leaks = False
        if leaks:
            print("valgrind found memory leaks, check your code for allocation/freeing errors and run the tests again")
            return True
    return False


def valgrind_test():
    print("running valgrind with full check and debug mode")

    with open("valgrind_test.txt", 'w') as out_file:
        try:
            valgrind = subprocess.run(
                "valgrind --leak-check=full --tool=memcheck --show-leak-kinds=all --track-origins=yes --verbose "
                f"--error-exitcode=1 -v --log-file=valgrind-log.txt ./{EXECUTABLE} -p 24 full8functionality8check -r 1 "
                "MyParameter=ParameterWithLongName http://localhost:5000/life_cycle",
                stdout=out_file, text=True, shell=True, timeout=20)

        except subprocess.TimeoutExpired:
            print("Timeout occurred.")
            return False

    if check_leaks():
        return False

    with open("valgrind_test.txt", "r") as output:
        try:
            content = output.read()

        except UnicodeDecodeError:
            return False

    if "Total received response bytes" not in content:
        return False

    return valgrind.returncode == 0


def life_cycle():
    with open("life_cycle_stdout.txt", "w") as output:
        try:
            client_proc = subprocess.run(["./ex2", "-p", "24",
                                          "full8functionality8check", "-r", "1",
                                          "MyParameter=ParameterWithLongName",
                                          "http://localhost:5000/life_cycle"],
                                         stdout=output,
                                         timeout=20)

        except (subprocess.TimeoutExpired, UnicodeDecodeError) as e:
            return False

    with open("life_cycle_stdout.txt", "rb") as output:
        try:
            content = output.read()
            OK200_start = content.find(b'HTTP/1.1 200 OK')
            OK200_end = content.rfind(b'Connection: close\r\n\r\n') + len(b'Connection: close\r\n\r\n')

        except UnicodeDecodeError:
            return False

    with open("server/templates/sample.html", "rb") as expected_output:
        expected = expected_output.read()

    requests = [b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.0\r\nHost: localhost\r\nContent-Length: '
                b'24\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.0\r\nHost: localhost\r\nContent-Length:'
                b'24\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.0\r\nHost: localhost\r\nContent-Length: '
                b'24\r\nConnection: close\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.0\r\nHost: localhost\r\nContent-Length:'
                b'24\r\nConnection: close\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.0\r\nHost: localhost\r\nConnection: close'
                b'\r\nContent-Length: 24\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.0\r\nHost: localhost\r\nConnection: close'
                b'\r\nContent-Length:24\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.1\r\nHost: localhost\r\nContent-Length: '
                b'24\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.1\r\nHost: localhost\r\nContent-Length:'
                b'24\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.1\r\nHost: localhost\r\nContent-Length: '
                b'24\r\nConnection: close\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.1\r\nHost: localhost\r\nContent-Length:'
                b'24\r\nConnection: close\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.1\r\nHost: localhost\r\nConnection: close'
                b'\r\nContent-Length: 24\r\n\r\nfull8functionality8check',
                b'POST /life_cycle?MyParameter=ParameterWithLongName HTTP/1.1\r\nHost: localhost\r\nConnection: close'
                b'\r\nContent-Length:24\r\n\r\nfull8functionality8check']

    printf1 = [b'HTTP request =\n' + req + b'\n' + b'LEN = ' + str(len(req)).encode() for req in requests]
    printf2 = b'Total received response bytes: ' + str(len(expected) + OK200_end - OK200_start).encode()

    with open("db.json", "r") as db_file:
        requests_wall = json.load(db_file)

    received = requests_wall[-1]

    if received['body'] != 'full8functionality8check':
        return False

    if not received.get('c_len'):
        return False

    if int(received['c_len']) != len('full8functionality8check'):
        return False

    if not received.get('params'):
        return False

    if ''.join(received['params'].values()) != 'ParameterWithLongName':
        return False

    if not any(pr1.lower() in content.lower() for pr1 in printf1):
        return False

    if expected not in content:
        return False

    if printf2 not in content:
        return False

    if client_proc.returncode != 0:
        return False

    return True


def get_parameters():
    with open("get_with_params_stdout.txt", "w") as output:
        try:
            # ParameterizedTest
            client_proc = subprocess.run(
                ["./ex2", "-r", "17", "1=P", "2=a", "3=r", "4=a", "5=m", "6=e", "7=t", "8=e", "9=r",
                 "10=i", "11=z", "12=e", "13=d", "14=T", "15=e", "16=s", "17=t", "http://localhost:5000/get_params"],
                stdout=output,
                timeout=20)

        except (subprocess.TimeoutExpired, UnicodeDecodeError) as e:
            return False

    with open("db.json", "r") as db_file:
        requests_wall = json.load(db_file)

    received = requests_wall[-1]

    if not received.get('params'):
        return False

    params = ''.join(received['params'].values())

    if params != "ParameterizedTest":
        return False

    if client_proc.returncode != 0:
        return False

    return True


def post():
    with open("post_request_stdout.txt", "w") as output:
        body = "Cross8Site8Scripting8XSS8attacks8are8a8type8of8injection8in8which8malicious8scripts8are8injected8" \
               "into8otherwise8benign8and8trusted8websites18XSS8attacks8occur8when8an8attacker8uses8" \
               "a8web8application8to8send8malicious8code8generally8in8the8form8of8a8browser8side8script8" \
               "to8a8different8end8user18Flaws8that8allow8these8attacks8to8succeed8are8quite8widespread8" \
               "and8occur8anywhere8a8web8application8uses8input8from8a8user8within8the8output8it8" \
               "generates8without8validating8or8encoding8it18An8attacker8can8use8XSS8to8send8a8" \
               "malicious8script8to8an8unsuspecting8user18The8end8users8browser8has8no8way8to8know8that8the8" \
               "script8should8not8be8trusted8and8will8execute8the8script18Because8it8thinks8the8" \
               "script8came8from8a8trusted8source8the8malicious8script8can8access8any8cookies8session8" \
               "tokens8or8other8sensitive8information8retained8by8the8browser8and8used8with8that8site18These8" \
               "scripts8can8even8rewrite8the8content8of8the8HTML8page18" \
               "Can8you8think8of8a8simple8way8to8compromise8EX2server8to8execute8additional8code3"
        try:
            client_proc = subprocess.run(["./ex2", "-p", "1004", body, "http://localhost:5000/post"],
                                         stdout=output,
                                         timeout=20)

        except (subprocess.TimeoutExpired, UnicodeDecodeError) as e:
            return False

        with open("db.json", "r") as db_file:
            requests_wall = json.load(db_file)

        received = requests_wall[-1]

        if not received.get('body'):
            return False

        if received['body'] != body:
            return False

        if not received.get('c_len'):
            return False

        if int(received['c_len']) != len(body):
            return False

        if client_proc.returncode != 0:
            return False

        return True


def pdf():
    with open("get_request_pdf_stdout.txt", "wb") as output:
        try:
            client_proc = subprocess.run(["./ex2", "http://localhost:5000/pdf"],
                                         stdout=output,
                                         timeout=20)
        except (subprocess.TimeoutExpired, UnicodeDecodeError) as e:
            return False

    with open("get_request_pdf_stdout.txt", "rb") as output:
        content = output.read()
        # start_pos = content.find(b'%PDF-1.3') - len(b'%PDF-1.3')

    with open("server/templates/pdf.pdf", "rb") as expected_output:
        expected_content = expected_output.read()

    if expected_content not in content:
        return False

    if client_proc.returncode != 0:
        return False

    return True


def get():
    with open("get_request_stdout.txt", "w") as output:
        try:
            client_proc = subprocess.run(["./ex2", "http://localhost:5000/get"],
                                         stdout=output,
                                         timeout=20)

        except (subprocess.TimeoutExpired, UnicodeDecodeError) as e:
            return False

    try:
        with open("get_request_stdout.txt", "r") as output:
            content = output.read()

    except UnicodeDecodeError:
        return False

    with open("server/templates/neverssl.html", "r") as expected_output:
        expected = expected_output.read()

    if expected not in content:
        return False

    if client_proc.returncode != 0:
        return False

    return True


def structure():

    expected = [b'GET /invalid/path HTTP/1.0\r\nHost: localhost\r\n\r\n',
                b'GET /invalid/path HTTP/1.1\r\nHost: localhost\r\n\r\n',
                b'GET /invalid/path HTTP/1.0\r\nHost: localhost\r\nConnection: close\r\n\r\n',
                b'GET /invalid/path HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n']

    with open("structure_stdout.txt", "wb") as output:
        try:
            client_proc = subprocess.run(
                ["./ex2", "http://localhost:5000/invalid/path"],
                stdout=output,
                timeout=20)

        except (subprocess.TimeoutExpired, UnicodeDecodeError) as e:
            return False

    with open("structure_stdout.txt", "rb") as output:
        try:
            content = output.read()

        except UnicodeDecodeError:
            return False

    if not any(req.lower() in content.lower() for req in expected):
        return False

    return True


def usage():
    with open("usage_stdout.txt", 'w') as output:
        try:
            client_proc = subprocess.run(
                ["./ex2", "-p", "17", "no http:// prefix", "-r", "2", "1=-1", "2=-2", "nohttpprefix.com"],
                stdout=output,
                timeout=10)

        except (subprocess.TimeoutExpired, UnicodeDecodeError) as e:
            return False

    with open("usage_stdout.txt", "r") as output:
        try:
            content = output.read()
            if content[:6].lower() != "usage:":
                return False

        except UnicodeDecodeError:
            return False

    return True


def setup():
    if os.path.isfile(EXECUTABLE):
        os.remove(EXECUTABLE)

    del_wall_req = requests.delete("http://localhost:5000/delete_wall")

    if del_wall_req.status_code != 200:
        raise "Delete Method Exception"

    with open("stdout_compilation.txt", 'w') as out_file:
        c = subprocess.run(
            f'gcc -Wall {C_FILES} -o {EXECUTABLE}',
            stderr=out_file,
            stdout=out_file,
            shell=True,
        )

    with open("stdout_compilation.txt") as out_file:
        res = out_file.read()
        return_val = None
        if bytes(res, 'utf-8') == b'':
            print("Ex. compiled successfully.")
            return_val = "Compiled"

        if "warning: " in res:
            print("Warnings during compilation")
            return_val = "Warnings"

        if "error: " in res:
            print("\nSomething didn't go right when compiling your C source "
                  "please check stdout_compilation.txt\n")
            return_val = "Error"

    return return_val


if __name__ == "__main__":
    compilation_status = setup()

    if compilation_status == "Error":
        exit(0)

    t_usage = usage()
    t_structure = structure()
    t_get = get()
    t_pdf = pdf()
    t_post = post()
    t_params = get_parameters()
    t_life_cycle = life_cycle()
    t_valgrind = valgrind_test()

    t = PrettyTable(['Test', 'Result'])
    t.align['Test'] = 'l'
    t.add_row(['Usage', t_usage])
    t.add_row(['Request Structure', t_structure])
    t.add_row(['Get Request', t_get])
    t.add_row(['PDF File', t_pdf])
    t.add_row(['Post Request', t_post])
    t.add_row(['Parameters', t_params])
    t.add_row(['Life Cycle', t_life_cycle])
    t.add_row(['Valgrind', t_valgrind])
    print(t)

    req = requests.get(f'http://localhost:5000/puzzle?usage={t_usage}&structure={t_structure}&get={t_get}&pdf={t_pdf}&'
                       f'post={t_post}&params={t_params}&life_cycle={t_life_cycle}&valgrind={t_valgrind}')


