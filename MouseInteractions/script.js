function appear(event) {
    let image = document.getElementById('myPicture'),
        newX = event.clientX,
        newY = event.clientY;

    image.style.left = (newX - (100 / 2)) + "px";
    image.style.top = (newY - (100 / 2)) + "px";

    image.style.visibility = 'visible';
}

function disappear() {
    let image = document.getElementById('myPicture');

    image.style.visibility = 'hidden';
}