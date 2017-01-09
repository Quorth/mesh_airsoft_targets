# mesh_airsoft_targets

![Assembled targets](https://raw.githubusercontent.com/Quorth/mesh_airsoft_targets/master/images/Assebled%20targets.jpg)

Completed targets (piezo still not glued)

An arduino based airsoft targets with mesh networking capabilities. This is a WIP project originally made for the Murcia Lan Party event. But since it's been stalled for more than a year, we decided to release

We use the nrlf24l01 2.4Ghz modem and the RF24Mesh library to comunicate the targets with the master module

![First boards](https://raw.githubusercontent.com/Quorth/mesh_airsoft_targets/master/images/First%20boards.jpg)

First boards

The targets can control a RGB LED and reports the impacts to the master node, the games are implemented in the master module, so far we only have a sequential game with timing implemented

The impact detection is implemented via a piezoelectric transducer and a opamp for cleaning the pulse and setting sensitivity, you have the eagle schematics in target_node/board

![Detecting an impact](https://raw.githubusercontent.com/Quorth/mesh_airsoft_targets/master/images/Detecting%20an%20impact.jpg)

Detecting an impact

The master module is an arduino board with a serial connection to the host the same board we use for the targets can be used as a master, but the idea is to eventually port to an OpenWRT target (like a TL703n) for networked operation or a BT link to a phone.
