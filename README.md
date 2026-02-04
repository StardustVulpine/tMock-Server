# Description and goals of the project
Hobbistic project with a goal to reimplement Terraria Server with C++ and learn more about Sockets, Server Networking and Terraria Network Protocol communication.
During development I use a set of tools and docummentation websites to help get up-to-date information about how Terraria Network Protocol (TNP) communicates, what messages structure looks like, what data types it uses.

## Tool and Resources used during development
- [Wireshark](https://www.wireshark.org/)'s network traffic analysis
- Terraria Native Server
- [Terrafirma Documentation](https://seancode.com/terrafirma/net.html)
- [TShock Documentation](https://tshock.readme.io/docs/multiplayer-packet-structure)


# Status

🛠️ **Under development**🛠️

Server handles client's connection, protocol version verification, requesting and recieving password and assigning player slot.

> [!NOTE]
> Currently only Linux is supported as it relies on builtin socket library.

## Roadmap

- [x] Phase 1 - Client Connection:
  - [x] Accept Connection from client (01) and reply with custom error message (02) 
  - [x] Request client for password (25), recieve password (26) and reply with custom error messages depending on password match
  - [x] Assign player slot replaying with (03) message
- [ ] Phase 2 - Handle Player & World Information:
  - [ ] Handle player information from client
  - [ ] Handle world information from client

## Currently Supported TNP Packets
| ID (int) | ID (byte) | Message Name | Direction |
| :---: | :---: | --- | --- |
|  1 | 0x01 | Connect Request | Client -> Server |
|  2 | 0x02 | Fatal Error / Disconnect | Server -> Client |
|  3 | 0x03 | Connection Approved / Assign Player Slot | Server -> Client |
| 37 | 0x25 | Request Password | Server -> Client |
| 38 | 0x26 | Send Password / Login with Passoword | Client -> Server |

# TNP packet structure details
Below are details about packet messages strucutres sent between Terraria's Server and Client that I currently managed to determine with help of Wireshark and avaliable documentation on the internet.
*(this section will be updated as project grows)*

## Packet Structure

Every packet sent in either direction uses the same base package structure.
| Offset | Byte Offset | Size (bytes) | Type | Description | Notes |
| :---: | :---: | :---: | :---: | --- | --- |
| 0-1 | 1-2 | 2 | Int16/short/short int | Lenght of whole packet in bytes | This value is always `3 + Payload's Byte Size` because it is a SUM of entire message size expressed in "how many bytes length the message is". Base Packet has size of 3 because first 2 bytes is for lenght and 3rd byte is for type, so 3 bytes length + lenght of rest of the message which depends on type and content of packet's data. |
|  2  |  3  | 1 | unsigned byte/byte/unsigned char/char | Packet Type / ID | ID of packet type represented as HEX byte value |
|  3+ |  4+ | ? | ? | Packet Data / Payload | Size and Type depends on message type |

## Payload / Packet Data Types

### Connect Request (1)

**Direction:** `Server ◄ Client`

**Type/ID:** `0x01`

This is the first message sent by the client to the server when it connects. It notifies server of the Terraria Network Protocol version client use.

<details open>
<summary>
  Structure Details
</summary>
  
| Offset | Byte Offset | Size (bytes) | Type | Description | Notes |
| :---: | :---: | :---: | :---: | --- | --- |
| 3 | 4 | 1 | unsigned byte/byte/unsigned char/char | Text Message Size |  |
| 4+ | 5+ | ? | String | Text Message Content | Content of this text message is always the word "Terraria" concatented with the current version of Network Protocol, ex. "Terraria279" - ("Terraria" + Main.curRelease) |

</details>

### Fatal Error / Disconnect (2)
**Direction:** `Server ► Client`

**Type/ID:** `0x02`

<details open>
<summary>
  Structure Details
</summary>
  
| Offset | Byte Offset | Size (bytes) | Type | Description | Notes |
| :---: | :---: | :---: | :---: | --- | --- |
|  3 |  4 | 1 | unsigned byte/byte/unsigned char/char | Network Text Mode | This can be one of:<br> ```LITERAL = 0x00```,<br> `FORMATTABLE = 0x01`,<br> `LOCALIZATION_KEY = 0x02`,<br> `SUBSTITUTION = 0x03`  |
|  4 |  5 | 1 | unsigned byte/byte/unsigned char/char | Text Message Size | Size of Text Message Content's sent in this packet |
| 5+ | 6+ | 1 | string | Text Message Content | Error Message's Text Content. Can be any message when used with `LITERAL` Text Mode. Terraria uses `LOCALIZATION_KEY` for most messages since this support errors display in multiple languages that are accessed by KEYS specified inside [json file](dev_resources/Terraria.Localization.Content.en-US.json). |

</details>

### Request Password (37)

**Direction:** `Server ► Client`

**Type/ID:** `0x25`

<details open>
<summary>
  Structure Details
</summary>
  
> This message has no data/payload. Server send's basic package of size `3 bytes` with type of `0x25` to client. When client recieves this type of packet, prompts user for password and when user type it, client send back to server packet [#38](#send-password--login-with-password-38)

</details>

### Send Password / Login with Password (38)

**Direction:** `Server ◄ Client`

**Type/ID:** `0x26`

This message is very similar to [#1](#connect-request-1). Client sends to a server packet with 

<details open>
<summary>
  Structure Details
</summary>
  
| Offset | Byte Offset | Size (bytes) | Type | Description | Notes |
| :---: | :---: | :---: | :---: | --- | --- |
| 3 | 4 | 1 | unsigned byte/byte/unsigned char/char | Text Message Size |  |
| 4+ | 5+ | ? | String | Text Message Content | Password send by client |

</details>


# Communication Schema
## Stage 1 - Initialize Connection
![Diagram showing communication schema](/dev_resources/TNP_Communication_Map.drawio.svg)

## Stage 2 - Sync Player & World Information
WIP

