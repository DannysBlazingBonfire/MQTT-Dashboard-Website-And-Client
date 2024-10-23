from flask import Blueprint, render_template
import psutil
import paho.mqtt.client as mqtt

views = Blueprint(__name__, 'views')

mqttClient = mqtt.Client()

# endpoints here
@views.route('/')
def index ():
    return render_template('index.html')

#Try gpiozero for temps on rpi
@views.route('server/stats')
def fetchDeviceStats(): 
    CPU_Usage = psutil.cpu_percent(interval=1.5, percpu=False)
    RAM_Usage = psutil.virtual_memory()[2]
    data = {'CPU_Usage' : CPU_Usage, 'RAM_Usage' : RAM_Usage}
    return data, 200

@views.route('server/connect/mqttBroker')
def connectToBroker():
    try:    
        mqttClient.username_pw_set(username='MQTT-USERNAME-HERE', password='MQTT-PASSWORD-HERE')
        mqttClient.connect(host='RASPBERRY-PI-IP-HERE', port=1883, keepalive=10)
        mqttClient.loop_start()
        return 'Connected', 200
    except Exception as e:
        print(f'Flask: could not connect to MQTT because {e}')
        return 'Disconnected', 500

@views.route('server/led/<state>')
def updateLed(state):
    try:
        mqttClient.publish(topic='dashboard/led', payload=f'{state}')
        return '', 200
    except Exception as e:
        print(f'could not update LED because: {e}')
        return f'Led not updated because {e}', 500
