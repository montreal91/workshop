
document.body.onload = do_something;

const d = [{x:0, y:1}, {x:0, y:0}]

function do_something() {
    console.log("something is happening");
    var div_element = document.createElement("div");
    div_element.innerHTML = "Something is happening";
    document.body.appendChild(div_element);
    Draw(document.getElementById("my_battlefield"));
}

var big_x = 0;

function IncreaseBigX() {
    big_x++;
    big_x %= 8;
    console.log(big_x);
}


function SetTabloidString(val) {
    var tabloid = document.getElementById("tabloid");
    tabloid.innerHTML = val;
}

function EraseTabloidString() {
    var tabloid = document.getElementById("tabloid");
    tabloid.innerHTML = "";
}

document.addEventListener("keyup", (event) => {
    const keyName = event.key;
    if (keyName === " ") {
        EraseTabloidString();
    }
    if (event.key == "ArrowRight") {
        IncreaseBigX();
    }
    Draw(document.getElementById("my_battlefield"));
}, false);

document.addEventListener("keypress", (event) => {
}, false);

function Draw(cnv) {
    ctx = cnv.getContext("2d");
    // ctx.fillStyle = "rgb(100, 150, 150)";
    ctx.clearRect(0, 0, cnv.width, cnv.height);
    ctx.fillStyle = "rgb(0, 30, 30)";
    ctx.fillRect(big_x * 50,0, 50, 50);

    for (var i=0; i < d.length; i++) {
        ctx.fillRect(d[i].x * 50, d[i].y * 50, 50, 50);
    }

    ctx.font = "20px Arial";
    ctx.fillText("Game Over", 100, cnv.height / 2);
}
