Coded-TCP-Multipath Development Milestones
==========================================

The following goals represent milestones for the development of the
multi-path CTCP project. In general, we would like to have a single
program that can act as either a client or server SOCKS5 proxy. When
acting as a client, the program should accept SOCKS5 proxy requests,
initiate a MPCTCP session with the remote server, and then complete
the session. When acting as a server, the program should accept
incoming MPCTCP session requests from a remote client and transfer all
data to that client via the MPCTCP protocol.  
  
Specific milestones for accomplishing the goals above include:  
  
### Working single-path UDP connection via SOCKS5
* Description: Two-way UDP session should be able to be setup via a SOCKS5 proxy.
* Tasks:
 * Develop front-end program for configuration file parsing and MPCTCP proxy setup
 * Develop standard networking functions. This includes functions that should be needed for multi-path transport.
 * Develop SOCKS5 procedure for communicating with SOCKS5 client
 * Develop procedure for initializing remote MPCTCP proxy
 * Test and verification  

### TCP over UDP, single-path
* Description: The two-way UDP session now behaves like a TCP session. This includes the three-way handshake done during session initiation, TCP congestion control, and session termination.
* Tasks:
 * Implement 3-way handshakes over UDP
 * Implement congestion control over UDP
 * Ensure that the code allows you to create/destroy a path without destroying the session
 * Test and verification  

### Sliding window coding, single-path  
* Description: All traffic between the client and server can now be coded, regardless of the direction of travel.
* Tasks:  
 * Determine the necessary feedback required to manage coding window
 * Implement estimators for determining packet loss
 * Implement coding algorithms
 * Implement decoding algorithms
 * Test and verification  

### Coded TCP over multiple paths  
* Description: Traffic should be able to be transmitted over multiple paths with the necessary code to allow for reconstruction of the appropriate bit stream on the opposite side.
* Tasks:
 * Implement interface selection
 * Develop path selection algorithms
 * Determine feedback requirements
 * Implement multi-path transport
 * Test and verification  

