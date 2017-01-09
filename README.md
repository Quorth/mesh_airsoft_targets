# mesh_airsoft_targets

An arduino based airsoft targets with mesh networking capabilities. This is a WIP project originally made for the Murcia Lan Party event. But since it's been stalled for more than a year, we decided to release

We use the nrlf24l01 2.4Ghz modem and the RF24Mesh library to comunicate the targets with the master module

The targets can control a RGB LED and reports the impacts to the master node, the games are implemented in the master module, so far we only have a sequential game with timing implemented

The impact detection is implemented via a piezoelectric transducer and a opamp for cleaning the pulse and setting sensitivity, you have the eagle schematics in target_node/board

The master module is an arduino board with a serial connection to the host.
