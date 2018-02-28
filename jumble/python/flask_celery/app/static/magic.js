
let counter = 0;
let socket = io.connect("http://" + document.domain + ":" + location.port + "/test/");

function start_countdown() {
  // axios.post("/start_countdown/", {
  //   time: 13
  // })
  // .then((response) => {
  //   let tablo = document.getElementById("tablo");
  //   tablo.innerHTML = response.data.time_to_wait;
  // })
  // .catch((error) => {
  //   alert(error);
  // });
  socket.emit("start_countdown", {loops: 13});
  return false;
}

function time_update(message) {
  let tablo = document.getElementById("tablo");
  tablo.innerHTML = message.remaining;
}

function ping() {
  socket.emit("ping");
}

function pong(message) {
  let div = document.getElementById("tablo2");
  div.innerHTML = message.message;
} 

function main() {
  socket.emit("connect");
  socket.on("countdown", time_update);
  socket.on("pong", pong);
}

document.body.onload = main;
