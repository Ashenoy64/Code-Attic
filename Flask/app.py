from flask import Flask
from flask import render_template,request

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html',loading='false')


@app.route('/login',methods=['POST','GET'])
def login():
    if request.method == 'GET':
        return render_template('login.html',loading='false')
    else:
        data = request.form 
        print(data)
        return render_template('login.html',loading='false')
@app.route('/<name>/<option>')
def name(name,option):
    option = int(option)
    if option == 1:
        return F1(name)
    elif option == 2:
        return F2(name)
    else:
        return F3(name)





def F1(name):
    return "Function one"+" "+name

app.add_url_rule('/test',F1,F1)

def F2(name):
    return "Function two"+" "+name

def F3(name):
    return "Function three"+" "+name



if __name__=="__main__":
    app.run(debug=True)