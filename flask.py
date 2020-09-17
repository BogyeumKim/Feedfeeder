import pymysql
from flask import Flask, render_template, request
db = pymysql.connect(host="localhost", port=3306, user="root", passwd="apmsetup", db="cksmart", charset='utf8')
app = Flask(__name__)
state='off'
@app.route('/')
def iii():
        return render_template('index.html', state=state)
@app.route('/on')
def input_to_database():
        global state
        name=request.args.get('name')
        cur = db.cursor()
        sql = "insert into wallcounter (wname, wdate) values ('%s', NOW());" % (name)
        cur.execute(sql)
        db.commit()
        return render_template('index.html', state=state)
        
@app.route('/off')
def input_to_database2():
        global state
        name=request.args.get('name')
        cur = db.cursor()
        sql = "insert into wallcounter (wname, wdate) values ('%s', NOW());" % (name)
        cur.execute(sql)
        db.commit()
        return render_template('index.html', state=state)
if __name__ == '__main__':
        print('Webserver ready...')
        app.run(host='0.0.0.0', port=8888)
        print('Webserver shutting down...')
        db.close()
