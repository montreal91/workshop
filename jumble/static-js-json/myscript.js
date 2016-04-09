function load() {
    var mydata = JSON.parse( data );
    var i;
    for ( i=0; i < mydata.length; i++ ) {
        $("#music-list").append("<div>" + mydata[i].name + " " + mydata[i].age + "</div>");
    }
}
