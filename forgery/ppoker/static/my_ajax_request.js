
function my_ajax() {
    forma = document.getElementById("my_form");
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            if (req.status != 200) {
            } else {
                var response = JSON.parse(req.responseText);
                document.getElementById("result").innerHTML = response.result;
                document.getElementById("clicks").innerHTML = response.clicks;
            }
        }
    }
    req.open('POST', '/_count_characters/');
    req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    var un = forma.my_text.value;
    var post_vars = 'text='+un;
    req.send(post_vars);
    return false;
}
