from flask import Flask, render_template, request
from gpiozero import PWMLED

# Comment GPIO Part out to test on PC#


# set up LEDs:
# red = PWMLED(17)
# green = PWMLED(27)
# blue = PWMLED(22)
red = 0
green = 0
blue = 0
led_values = [0, 0, 0]
app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def main():
    if len(request.form) > 0:
        led_values[0] = float(request.form["redvalue"])
        print(led_values[0])
        led_values[1] = float(request.form["greenvalue"])
        led_values[2] = float(request.form["bluevalue"])

    return render_template("basicTemplate.html", red=led_values[0], green=led_values[1], blue=led_values[2])


@app.route("/off")
def off():
    led_values[0] = 0
    print(led_values[0])
    led_values[1] = 0
    led_values[2] = 0
    return render_template("basicTemplate.html", red=led_values[0], green=led_values[1], blue=led_values[2])


@app.route("/on")
def on():
    led_values[0] = 1023
    print(led_values[0])
    led_values[1] = 1023
    led_values[2] = 1023
    return render_template("basicTemplate.html", red=led_values[0], green=led_values[1], blue=led_values[2])


###mobile layout:
@app.route("/mobile", methods=["GET", "POST"])
def main_mobile():
    if len(request.form) > 0:
        led_values[0] = float(request.form["redvalue"])
        print(led_values[0])
        led_values[1] = float(request.form["greenvalue"])
        led_values[2] = float(request.form["bluevalue"])

    return render_template("mobileTemplate.html", red=led_values[0], green=led_values[1], blue=led_values[2])


@app.route("/mobile/off")
def off_mobile():
    led_values[0] = 0
    print(led_values[0])
    led_values[1] = 0
    led_values[2] = 0
    return render_template("mobileTemplate.html", red=led_values[0], green=led_values[1], blue=led_values[2])


@app.route("/mobile/on")
def on_mobile():
    led_values[0] = 1023
    print(led_values[0])
    led_values[1] = 1023
    led_values[2] = 1023
    return render_template("mobileTemplate.html", red=led_values[0], green=led_values[1], blue=led_values[2])


@app.route("/get_values")
def get_values():
    # red_int = int(led_values[0])
    # print("Value send to Arduino" + str(led_values[0]))
    str_return = str(int(led_values[0])) + "," + str(int(led_values[1])) + "," + str(int(led_values[2]))
    return str_return


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80, debug=False)
