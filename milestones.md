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
  
1. Working single-path UDP connection via SOCKS5  
	a. Description: Two-way UDP session should be able to be setup via
	   a SOCKS5 proxy.  
	b. Tasks:  
		i. Develop front-end program for configuration file parsing 
		   and MPCTCP proxy setup  
		ii. Develop standard networking functions. This includes 
		    functions that should be needed for multi-path transport.  
		iii. Develop SOCKS5 procedure for communicating with SOCKS5 
		     client  
		iv. Develop procedure for initializing remote MPCTCP proxy  
		v. Test and verification  

2. TCP over UDP, single-path  
	a. Description: The two-way UDP session now behaves like a TCP 
	   session. This includes the three-way handshake done during 
	   session initiation, TCP congestion control, and session 
	   termination.  
	b. Tasks:  
		i. Implement 3-way handshakes over UDP  
		ii. Implement congestion control over UDP  
		iii. Ensure that the code allows you to create/destroy a
		     path without destroying the session  
		iv. Test and verification  

3. Sliding window coding, single-path  
	a. Description: All traffic between the client and server can now 
	   be coded, regardless of the direction of travel.  
	b. Tasks:  
		i. Determine the necessary feedback required to manage coding
		   window  
		ii. Implement estimators for determining packet loss  
		iii. Implement coding algorithms  
		iv. Implement decoding algorithms  
		v. Test and verification  

4. Coded TCP over multiple paths  
	a. Description: Traffic should be able to be transmitted over 
	   multiple paths with the necessary code to allow for 
	   reconstruction of the appropriate bit stream on the opposite 
	   side.  
	b. Tasks:  
		i. Implement interface selection  
		ii. Develop path selection algorithms  
		iii. Determine feedback requirements  
		iv. Implement multi-path transport  
		v. Test and verification  

