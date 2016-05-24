var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(
    75,
    window.innerWidth / window.innerHeight,
    0.1,
    1000
);

var renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

var geometry = new THREE.BoxGeometry( 1, 1, 1 );
var material = new THREE.MeshLambertMaterial( { color: 0x00ff00 } );
var cube = new THREE.Mesh( geometry, material );
scene.add( cube );

var light = new THREE.AmbientLight( 0x404040, 0.5 ); // soft white light
scene.add( light );

var geometry = new THREE.TorusGeometry( 4, 1, 16, 100 );
var material = new THREE.MeshLambertMaterial( { color: 0xffff00 } );
var torus = new THREE.Mesh( geometry, material );
scene.add( torus );

var light1 = new THREE.PointLight( 0x404040, 4, 100 );
light1.position.set( 3, 3, 0 );
scene.add( light1 );

camera.position.x = 3;
camera.position.y = 3;
camera.position.z = 5;
camera.lookAt( new THREE.Vector3( 0, 0, 0 ) );

var render = function() {
    requestAnimationFrame( render );

    cube.rotation.x += 0.035;
    cube.rotation.y += 0.035;
    renderer.render( scene, camera );
};

render();
