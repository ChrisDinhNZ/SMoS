# SMoS Generic Content Example

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
The use cases will be as follow:

1. [The *Controller* can request the *Edge Device* what is the state of the *Switch*](#the-controller-can-request-the-edge-device-what-is-the-state-of-the-switch)
2. [The *Controller* can request the *Edge Device* to turn the *Switch* on](#the-controller-can-request-the-edge-device-to-turn-the-switch-on)
3. [The *Controller* can request the *Edge Device* to turn the *Switch* off](#the-controller-can-request-the-edge-device-to-turn-the-switch-off)
4. The *Controller* can request the *Edge Device* what is the state of the *Alarm*
5. The *Controller* can request the *Edge Device* that it wants to be notified when state of the *Alarm* changes
6. If observed, when the *Alarm* turns on, the *Edge Device* will indicate the *Controller* the *Alarm* is on
7. If observed, when the *Alarm* turns off, the *Edge Device* will indicate the *Controller* the *Alarm* is off
8. The *Controller* can request the *Edge Device* that it no longer wants to be notified when state of the *Alarm* changes

From the system point of view, *Edge Device* is a server with 2 resources i.e. the *Switch* and the *Alarm*.
The *Controller* is the client.

Custom defined data content. In this case, we will defined the first byte to represent the resource:

* 0x01 = Switch
* 0x02 = Alarm

the second byte to represent the resource's state:
* 0x00 = OFF
* 0x01 = ON

### Message Examples

#### The *Controller* can request the *Edge Device* what is the state of the *Switch*

* Start Code = ':'
* Byte Count = 1
* Context Type = Confirmable
* Content Type = Generic content
* Content Type Options = None
* Code Class = Request
* Code Detail = GET
* Message Id = Sender defined (e.g. 0x1)
* Token Id = 0
* Data Content = 0x01
* Checksum = "0xED"

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 4 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0x10 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 6 | 1 | 1 | 1 | 0 | 1 | 1 | 0 | 1 | 0xED |

SMoS Hex string = ":0100011001ED"

When the edge device received a request for the state of the switch, it can either respond with an ACK follow by a separate response indicating the switch state or it can respond with an ACK and the switch state included (i.e piggy back response). The following is an example of a piggy back response indicating the switch is on.

* Start Code = ':'
* Byte Count = 2
* Context Type = ACK
* Content Type = Generic content
* Content Type Options = None
* Code Class = SUCCESS
* Code Detail = CONTENT
* Message Id = Sender defined (e.g. 0x1)
* Token Id = 0
* Data Content = 0x0101
* Checksum = "27"

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0x02 |
| 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x80 |
| 3 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 1 | 0x45 |
| 4 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0x10 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 0 | 1 | 0 | 0 | 1 | 1 | 1 | 0x27 |

SMoS Hex string = ":02804510010127"

#### The *Controller* can request the *Edge Device* to turn the *Switch* on

* Start Code = ':'
* Byte Count = 2
* Context Type = Confirmable
* Content Type = Generic content
* Content Type Options = None
* Code Class = Request
* Code Detail = PUT
* Message Id = Sender defined (e.g. 0x2)
* Token Id = 0
* Data Content = 0x0101
* Checksum = "0xD9"

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0x02 |
| 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0x03 |
| 4 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0x20 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 1 | 1 | 0 | 1 | 1 | 0 | 0 | 1 | 0xD9 |

SMoS Hex string = ":020003200101D9"

When the edge device received a request to change the state of the switch, it can either respond with an ACK follow by a separate response or it can respond with an ACK plus the outcome of the request included (i.e piggy back response). The following is an example of a separate response (the edge device will ACK the request, then separately send the response).

* Start Code = ':'
* Byte Count = 0
* Context Type = Acknowledgement 
* Content Type = 0
* Content Type Options = 0
* Code Class = 0
* Code Detail = 0
* Message Id = Sender defined (e.g. 0x2)
* Token Id = 0
* Data Content = 0
* Checksum = "0x60"

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 2 | 8 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x80 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0x20 |
| 7 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0x60 |

SMoS Hex string = ":0080002060"

Note that an ACK response without piggy-backed data is an empty message with only the message ID to map to the request. This indicates to the sender that the request has been received and that a response will be provided shortly.

Once we have a response ready we can send it to the original sender. However since we already acknowledged the original request we will need to use a new message ID. If we want an acknowledgement to this respone then we can send it as a confirmable message but in this example we don't, so send it as a non-confirmable message.

* Start Code = ':'
* Byte Count = 2
* Context Type = Non Confirmable 
* Content Type = Generic content
* Content Type Options = None
* Code Class = Success
* Code Detail = CHANGED
* Message Id = Sender defined (e.g. 0x4)
* Token Id = 0
* Data Content = 0x0101
* Checksum = "0x38"

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0x02 |
| 2 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0x40 |
| 3 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0x44 |
| 4 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0x40 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 7 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0x38 |

SMoS Hex string = ":02404440010138"

#### The *Controller* can request the *Edge Device* to turn the *Switch* off

* Start Code = ':'
* Byte Count = 2
* Context Type = Confirmable
* Content Type = Generic content
* Content Type Options = None
* Code Class = Request
* Code Detail = PUT
* Message Id = Sender defined (e.g. 0x3)
* Token Id = 0
* Data Content = 0x0100
* Checksum = "DA"

| Byte Index | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Hex Value |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 | 0x3A |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0x02 |
| 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0x03 |
| 4 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0x20 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0x01 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
| 7 | 1 | 1 | 0 | 1 | 1 | 0 | 1 | 0 | 0xDA |

SMoS Hex string = ":020003200100DA"

