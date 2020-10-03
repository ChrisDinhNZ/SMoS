# SMoS Example

* <- [Back](README.md)

![Simple GPIO Setup](images/smos_example.png)

Lets consider the above scenario, which consists of the following components:

###### Controller

A user controlled or automated device which communicates with the edge device using SMoS messages over a wired/wireless serial connection.
This device will have a SMoS codec to handle messages to/from the edge device.

###### Edge Device

A device that act as an interface between the digital world and the real world.
It communicates with the Controller using SMoS messages over a wired/wireless serial connection.
This device will have a SMoS codec to handle messages to/from the Controller.
It has a digital output pin which connects to a relay/switch.
It has a digital input pin which connects to an alarm.

###### Switch

An electrical switch which connects to the Edge Device's digital output pin.
It takes the signal from the Edge Device and set it's state to on/off.

###### Alarm

An alarm which connects to the Edge Device's digital input pin.
When it's circuit breaks, it will send a signal to the Edge Device and indicates the alarm is on/off.

From the Controller point of view, we want to be able to control the Switch and get notified when the alarm is on or off.
For simplicity, we will use unconfirmed messaging i.e when the receiver receives a message it will act on the message but will not acknowledge the sender.
The use cases will be as follow:

1. The *Controller* can request the *Edge Device* what is the state of the *Switch*
2. The *Controller* can request the *Edge Device* to turn the *Switch* on
3. The *Controller* can request the *Edge Device* to turn the *Switch* off
4. The *Controller* can request the *Edge Device* what is the state of the *Alarm*
5. The *Controller* can request the *Edge Device* that it wants to be notified when state of the *Alarm* changes
6. If observed, when the *Alarm* turns on, the *Edge Device* will indicate the *Controller* the *Alarm* is on
7. If observed, when the *Alarm* turns off, the *Edge Device* will indicate the *Controller* the *Alarm* is off
8. The *Controller* can request the *Edge Device* that it no longer wants to be notified when state of the *Alarm* changes

From the system point of view, *Edge Device* is a server with 2 resources i.e. the *Switch* and the *Alarm*.
The *Controller* is the client.

### SMoS Generic Content Example

Custom defined data content. In this case, we will defined the first byte to represent the resource:

* 0x01 = Switch
* 0x02 = Alarm

the second byte to represent the resource's state:
* 0x00 = OFF
* 0x01 = ON

##### Message Examples

###### The *Controller* can request the *Edge Device* what is the state of the *Switch*

* Start Code = ':'
* Byte Count = 1
* Context Type = Non confirmable
* Content Type = Generic content
* Content Type Options = None
* Code Class = Request
* Code Detail = GET
* Message Id = Sender defined
* Token Id = 0
* Data Content = 0x01
* Checksum = ""

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 2 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0x40 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 4 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0x10 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x73 |

**SMoS message** = "3A014001100173"

###### The *Controller* can request the *Edge Device* to turn the *Switch* on

###### The *Controller* can request the *Edge Device* to turn the *Switch* off

###### The *Controller* can request the *Edge Device* what is the state of the *Alarm*

###### The *Controller* can request the *Edge Device* that it wants to be notified when state of the *Alarm* changes

###### If observed, when the *Alarm* turns on, the *Edge Device* will indicate the *Controller* the *Alarm* is on

###### If observed, when the *Alarm* turns off, the *Edge Device* will indicate the *Controller* the *Alarm* is off

###### The *Controller* can request the *Edge Device* that it no longer wants to be notified when state of the *Alarm* changes

### SMoS BLE GATT Content Example