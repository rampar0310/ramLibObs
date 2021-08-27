// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
console.log("I m in render process");
const {ipcRenderer } = require('electron'); 

const startButton = document.getElementById('StartButton');

startButton.addEventListener("click", function(event) {

    console.log("Start Button clicked");
    ipcRenderer.send("start", "Start the Service");
    ipcRenderer.on("reply", (event, data) => {
        console.log(data);
    })

});


const stopButton = document.getElementById('StopButton');

    stopButton.addEventListener("click", function(event) {
    ipcRenderer.send("stop", "Stop the Service");
    ipcRenderer.on("reply", (event, data) => {
        console.log(data);

console.log("Stop Button clicked");

});


