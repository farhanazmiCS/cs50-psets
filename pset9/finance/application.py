import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Select query to return all of the values (e.g companyName) that a logged in user ownes. Returns a list containing dictionaries.
    stocks = db.execute(
        "SELECT companyName, companySymbol, price, SUM(share) AS shares FROM transactions WHERE user_id = ? GROUP BY companyName", session["user_id"])

    # Stores lists of dictionaries into a new list to include live price data
    stock_info = []

    # Initialise the grand total
    grand_total = 0

    # Select query "cash" returns list containing dictionaries
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    # Accessing a column and row in the query
    cash_owned = float(cash[0]["cash"])

    # For loop to "copy" dictionary content into new list of dictionaries plus new columns such as live price and total live price
    for row in stocks:

        if row["shares"] == 0:

            row["name"] = None
            row["symbol"] = None
            row["shares"] = None
            row["liveprice"] = None
            row["price"] = None
            row["total"] = None

        else:

            row["name"] = row["companyName"]
            row["symbol"] = row["companySymbol"]
            row["shares"] = row["shares"]
            call = lookup(row["symbol"])
            row["liveprice"] = round(call["price"], 2)
            row["price"] = row["price"]
            row["total"] = round(row["liveprice"] * row["shares"], 2)
            stock_info.append(row)
            grand_total += row["total"]

    # Grand total of stocks + balance
    grand_total += cash_owned

    # Function to check if user owns any stocks, if all sold, display different page
    if all(row["shares"] == stocks[0]["shares"] == None for row in stocks):

        # Return page showing that user does not own any shares if condition is true
        return render_template("indexnone.html", cash=cash_owned)

    return render_template("index.html", stocks=stock_info, cash=cash_owned, total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get input symbol from user
        sym = request.form.get("symbol")
        symbol = lookup(sym)

        # Get the number of shares from user
        shares = request.form.get("shares")

        # Check if user enters numeric value.
        if not shares.isnumeric():
            return apology("Enter numeric value.")

        share = int(shares)

        # Error check
        if not sym:
            return apology("Please enter the symbol of the company you would like to purchase.")
        if not symbol:
            return apology("Company not found or Invalid input. Try again.")
        if not shares:
            return apology("Please enter number of shares you would like to purchase.")

        # Error checking for shares
        if share < 0:
            return apology("Ensure non-negative value.")

        if not isinstance(share, int):
            return apology("Enter non-fractional or non-decimal numerical value")

        # Retrieve live price and companyName information
        price = symbol["price"]
        companyName = symbol["name"]

        # Total price to buy
        total_to_buy = price * share

        # Tag the transaction as "buy"
        tag = 'Buy'

        # Retrieve cash balance information and change it from a list(dict) format to a numeric value
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        check_cash = cash[0]["cash"]

        # If total is more than cash balance, return apology
        if total_to_buy > check_cash:
            return apology("Insufficient funds.")

        # Otherwise, insert the transaction into database
        insert_purchase = db.execute("INSERT INTO transactions (companyName, companySymbol, share, price, tag, user_id) VALUES (?, ?, ?, ?, ?, ?)",
                                                                                                                    companyName, sym, share, price, tag, session["user_id"])

        # Subtract the total amount from balance
        new_balance = check_cash - total_to_buy

        # Update the new balance into the database
        update_balance = db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        # Redirect user to home page to view his/her holdings
        return redirect("/")

    elif request.method == "GET":
        # Render buy form
        return render_template("buy.html")


@app.route("/buyindex", methods=["GET", "POST"])
@login_required
def buyindex():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get input symbol from user
        sym = request.form.get("symbol")
        symbol = lookup(sym)

        # Get the number of shares from user
        shares = request.form.get("shares")

        # Check if user enters numeric value.
        if not shares.isnumeric():
            return apology("Enter numeric value.")

        share = int(shares)

        # Error check
        if not sym:
            return apology("Please enter the symbol of the company you would like to purchase.")
        if not symbol:
            return apology("Company not found or Invalid input. Try again.")
        if not shares:
            return apology("Please enter number of shares you would like to purchase.")

        # Error checking for shares
        if share < 1:
            return apology("Invalid order. Try again")

        if not isinstance(share, int):
            return apology("Enter non-fractional or non-decimal numerical value")

        # Retrieve live price and companyName information
        price = symbol["price"]
        companyName = symbol["name"]

        # Total price to buy
        total_to_buy = price * share

        # Tag the transaction as "buy"
        tag = 'Buy'

        # Retrieve cash balance information and change it from a list(dict) format to a numeric value
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        check_cash = cash[0]["cash"]

        # If total is more than cash balance, return apology
        if total_to_buy > check_cash:
            return apology("Insufficient funds.")

        # Otherwise, insert the transaction into database
        insert_purchase = db.execute("INSERT INTO transactions (companyName, companySymbol, share, price, tag, user_id) VALUES (?, ?, ?, ?, ?, ?)",
                                                                                                                    companyName, sym, share, price, tag, session["user_id"])

        # Subtract the total amount from balance
        new_balance = check_cash - total_to_buy

        # Update the new balance into the database
        update_balance = db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        # Redirect user to home page to view his/her holdings
        return redirect("/")

    elif request.method == "GET":

        # Requesting symbol and no. of shares data from users
        search_sym = db.execute(
            "SELECT DISTINCT companySymbol, companyName, sum(share) AS shares FROM transactions WHERE user_id = ? GROUP BY companySymbol", session["user_id"])

        # Declare empty list to store dictionaries
        stock_info = []

        # Loop through the list for dicts
        for row in search_sym:
            if row["shares"] == 0:
                row["symbol"] = None
                row["shares"] = None
                row["name"] = None
                row["price"] = None
                row["total"] = None

            else:
                row["symbol"] = row["companySymbol"]
                row["name"] = row["companyName"]
                row["shares"] = row["shares"]
                call = lookup(row["symbol"])
                row["price"] = round(call["price"], 2)
                row["total"] = round(call["price"] * row["shares"], 2)
                stock_info.append(row)

        # Render buyindex form
        return render_template("buyindex.html", stocks=stock_info)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Select query to return all of the values (e.g companyName) that a logged in user ownes. Returns a list containing dictionaries.
    stocks = db.execute(
        "SELECT companyName, companySymbol, ABS(share) AS shares, price, timestamp, tag FROM transactions WHERE user_id = ?", session["user_id"])
    # Render "history.html" and parse values
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symbol = lookup(request.form.get("symbol"))

        if not symbol:

            return apology("Company not found. Try again.")

        return render_template("quoted.html", quote=symbol)

    elif request.method == "GET":

        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:

            return apology("Please enter a username.")

        elif not password:

            return apology("Please enter a password.")

        elif not confirmation:

            return apology("Please confirm password.")

        elif password != confirmation:

            return apology("Passwords do not match.")

        searchName = db.execute("SELECT username FROM users")

        for row in searchName:

            if username == row["username"]:

                return apology("Username taken.")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        return redirect("/register")

    elif request.method == "GET":

        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # get symbol from user
        symbol = request.form.get("symbol")
        # check number of shares the company has with input of companySymbol
        check_shares = db.execute(
            "SELECT companyName, SUM(share) AS shares FROM transactions WHERE user_id = ? AND companySymbol = ?", session["user_id"], symbol)
        # Retrieve the number of shares that the user wants to sell
        share = request.form.get("shares")
        # Retrieve companyName
        name = check_shares[0]["companyName"]

        # Check for input
        if not symbol or symbol is None:
            return apology("Please choose a stock you would like to sell")
        elif share is None:
            return apology("Please enter valid number of shares")

        # Check if user has enough shares to sell
        if int(share) > int(check_shares[0]["shares"]):
            return apology("Not enough shares to sell.")

        # lookup live price of the company
        check_price = lookup(symbol)
        share_price = check_price["price"]

        # total up the price and place negative in front
        total_to_sell = round(share_price * int(share), 2)

        # tag the transaction as "sell"
        tag = 'Sell'

        # Insert the "sold" transaction into a new table called "sold"
        sold = db.execute("INSERT INTO transactions (companyName, companySymbol, share, price, user_id, tag) VALUES (?, ?, ?, ?, ?, ?)",
                                                                                                             name, symbol, -int(share), share_price, session["user_id"], tag)
        # retrieve current balance (current balance is after buying stocks)
        get_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        current_balance = get_balance[0]["cash"]

        # update balance
        new_balance = current_balance + total_to_sell
        update_balance = db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        return redirect("/")

    elif request.method == "GET":

        # Requesting symbol and no. of shares data from users
        search_sym = db.execute(
            "SELECT DISTINCT companySymbol, companyName, sum(share) AS shares FROM transactions WHERE user_id = ? GROUP BY companySymbol", session["user_id"])
        # Declare empty list to store dictionaries
        stock_info = []
        # Loop through the list for dicts
        for row in search_sym:
            if row["shares"] == 0:
                row["symbol"] = None
                row["shares"] = None
                row["name"] = None
                row["price"] = None
                row["total"] = None

            else:
                row["symbol"] = row["companySymbol"]
                row["name"] = row["companyName"]
                row["shares"] = row["shares"]
                call = lookup(row["symbol"])
                row["price"] = round(call["price"], 2)
                row["total"] = round(call["price"] * row["shares"], 2)
                stock_info.append(row)

        return render_template("sell.html", stocks=stock_info)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
