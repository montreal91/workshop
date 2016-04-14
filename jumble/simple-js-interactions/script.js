
var text1 = "<p>Some fucking text!</p>";
var text2 = "<p>Another fucking text!</p>";
var header1 = "<h1>Title 1</h1>";
var header2 = "<h1>Title 2</h2>";

var state = 0;

function render_state() {
    var container = document.getElementById("container");
    if (state === 0) {
        container.innerHTML = header1 + text1;
    } else if (state === 1) {
        container.innerHTML = header2 + text2;
    } else {
        container.innerHTML = "<p>Something is fucked up!</p>";
    }
}

function change_state() {
    state++;
    state %= 2; // To ensure state can be only 0 and 1
}

function process_button_click() {
    change_state();
    render_state();
}

window.addEventListener('load', render_state);
