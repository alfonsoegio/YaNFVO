# SmartNFVO

SmartNFVO is the NFV smart orchestrator

## What is this about?

During last year I was introduced to a new
paradigm in computer science taking part
in some projects regarding the Network Function
Virtualisation ecosystem mainly based in the
European Telecommunications Standards Institute NFV-standard.

The experience is currently very challenging, but
after many times facing the same problems, the feeling
I have is that the NFV standard it's not production
ready in order to meet the needs of function vendors
and network operators.

The main reason behind the problems faced when
trying to build NFV systems that really work has not
to do with some lack of feature coverage in the standards
neither
the quality of the tools and projects intended to operate
this kind of service management and orchestration systems;
my thoughts about this systems usually have to do with the fact
that maybe we are trying to solve a problem
without the right tools, twisting the approach to meet particular
needs here and there when trying to adapt real systems
to meet the NFV paradigm and perform real stuff at the same time.

### Descriptors, templates and friends

The NFV standard consists of an specification
about how to describe services and it's life-cycle
management. All the approaches to implement systems
dealing with that kind of descriptors rely their
operation on a mix of three features:

- Format translation of static descriptors:
in order to be as agnostic as possible
(translating part of the descriptor as an Openstack
Heat Template (TeNOR) or some input information
for an LXD container host OSM, etc ...)

- Information retrieval:
after conversion and deployment on the Virtualised
Infrastructure Manager (VIM), the NFV-orchestrator
retrieves (usually asynchronously) the information
regarding the provisioned resources like MAC addresses,
IPs, net masks, etc ...

- Lifecycle management:
Either delegating in some middle-ware or not, the NFV-orchestrator
usually executing configuration scripts on the machines using
private keys generated in the VIM or passed by the orchestrator
itself according to operator requests, etc ... 

