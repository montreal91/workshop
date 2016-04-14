
var my_story = JSON.parse( paragraphs );

var state = 0;


function render_state() {
    var container = document.getElementById("container");
    var i;
    for (i = 0; i < my_story.length; i++) {
        if (state === my_story[i].id) {
            container.innerHTML = my_story[i].text;
            var dirs = my_story[i].directions;
            var j;
            for (j = 0; j < my_story[i].directions.length; j++) {
                var button = document.createElement('button');
                var current_direction = my_story[i].directions[j];
                button.innerHTML = current_direction;
                (function (cd) {
                    button.addEventListener('click', function() {
                        change_state(cd);
                        render_state();
                    });
                })(current_direction);
                container.appendChild(button);
            }
        }
    }
}

function change_state(e) {
    state = e;
}
