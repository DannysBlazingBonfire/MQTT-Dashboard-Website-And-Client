window.onload = function() {
    const htmlPiStatus = document.getElementById('pistats');
    const htmlMqttConnection = document.getElementById('BrokerConnection');
    setInterval(fetchRaspberryPiStats, 2000, htmlPiStatus);
    connectToBroker(htmlMqttConnection);
};

function fetchRaspberryPiStats(htmlPiStatus) {
    text = '';
    try {
        fetch('server/stats')
        .then((jsonData) => jsonData.json())
        .then((data) => {
            text = `Temp: N/A°C<br> CPU Usage: ${data.CPU_Usage}%<br> RAM Usage: ${data.RAM_Usage}%`;
            htmlPiStatus.innerHTML = text;
        })
        .catch((error) => {
            console.log(error);
            text = `Temp: N/A°C<br> CPU Usage: NA%<br> RAM Usage: NA%`;
            htmlPiStatus.innerHTML = text;
        })
    } catch (e) {
        console.log(`cant fetch PI stats because of: ${e}`);
    }
};

function connectToBroker(htmlMqttConnection) {
    text='';
    try {
        fetch('server/connect/mqttBroker')
        .then((response) => response.text())
        .then((data) => {
            htmlMqttConnection.innerHTML += data;
        })
    } catch(e) {
        console.log(`Cant connect because: ${e}`);
    }
}

function updateLed(ledStatus) {
    try {
        fetch(`server/led/${ledStatus}`);
    } catch(e) {
        console.log(`could not update LED because ${e}`);
    }
}