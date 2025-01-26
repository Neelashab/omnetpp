package wmn;

import inet.node.inet.StandardHost; // Defines a basic network node
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator; // Configures IP addresses and routing
import inet.mobility.static.StationaryMobility; // Mobility model for stationary nodes
import inet.linklayer.common.WirelessInterface; // Wireless interface module

module MeshNode
{
    parameters:
        string mobilityType = default("StationaryMobility");
    submodules:
        host: StandardHost {
            parameters:
                mobility.typename = mobilityType;
        }
        wlan: WirelessInterface {  // Explicitly define the wireless interface
            @class("AdhocHost");
        }
    connections:
        wlan.radioIn <--> host.pppg[0];
}

network SimpleWMN
{
    parameters:
        int numNodes = default(5);  // Number of nodes in the mesh network

    submodules:
        // Configurator to manage IP and routing setup
        configurator: Ipv4NetworkConfigurator {
            @display("p=100,100");
        }

        // Define `numNodes` MeshNode nodes in the network
        node[numNodes]: MeshNode {
            parameters:
                @display("p=100+200*cos(pi/2+i*2*pi/numNodes),100+200*sin(pi/2+i*2*pi/numNodes)"); // Circular layout
        }

    connections allowunconnected:
        // Connect every pair of nodes
        for i=0..numNodes-2, for j=i+1..numNodes-1 {
            node[i].wlan.radioIn <--> node[j].wlan.radioIn;  // Correct the connection
        }
}
