from flask import Flask, render_template, request, redirect, url_for
from runaddition import addition

app = Flask(__name__)

# User data - in a real-world scenario, this should be stored securely in a database
users = {'admin': 'admin'}


@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            # Redirect to the calculator page on successful login
            # return redirect('/calculator', username=username)
            return redirect(url_for('calculator', username=username))
        else:
            # Render login page with error message
            return render_template('login.html', error='Invalid username or password')
    else:
        # Render login page
        return render_template('login.html')


@app.route('/calculator', methods=['GET', 'POST'])
def calculator():
    username = request.args.get('username')
    if request.method == 'POST':
        num1 = int(request.form['num1'])
        num2 = int(request.form['num2'])
        username = request.form['username']
        # sum = num1 + num2
        # ---- call sgx code ----
        sum = addition(num1, num2)
        # Render calculator page with sum result
        return render_template('calculator.html', num1=num1, num2=num2, sum=sum, username=username)
    else:
        # Render calculator page
        return render_template('calculator.html', username=username)


if __name__ == '__main__':
    app.run(debug=True)
