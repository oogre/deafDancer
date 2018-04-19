using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class oscReceiver : MonoBehaviour {

    public string remoteIP = "127.0.0.1";
    public int ListenerPort = 12345;
    public int SendToPort = 57131;
    public Osc handler;
    public UDPPacketIO udp;
    [Range(0.0f, 1.0f)]
    public float randomLinear;
    [Range(0.0f, 1.0f)]
    public float noise;
    [Range(0.0f, 1.0f)]
    public float noiseFractal;
    void Start () {
        udp.init(remoteIP, SendToPort, ListenerPort);
        handler.init(udp);
        handler.SetAddressHandler("/deafDancer", ListenEvent);

    }

    public void ListenEvent(OscMessage oscMessage){
        noiseFractal = (float)oscMessage.Values[5];
    } 

}
