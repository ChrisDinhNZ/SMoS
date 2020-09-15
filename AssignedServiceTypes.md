## Assigned Service Types

#### 0x00 Reserved

---

#### 0x01 Toggle Service

The Toggle service allows the sender to query the state, update the state or be notified of state changes of a property.

Supported message types:
* Read
* Update
* Notify

Content length:
* 1 byte

Content details:
* An Id representing a property exposed by this service

Usage:
* `0x2A02000001010223` Query state of property with Id of 2
* `0x2A04000001010223` Toggle state of property with Id of 2
* `0x2A10000001010223` Report state of property with Id of 2

---

[Home](README.md)