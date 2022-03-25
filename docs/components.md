# StreamWork Components

The StreamWork project provides a set of tested, re-entrant, standard StreamWork components, available at [GitHub/tyoung3/sw](https://github.com/tyoung3/sw).

Standard components communicate over Go channel interfaces.  StreamWork components are contained as exported functions within Go packages.  They are documented, by package(SwBase, SwUtility, etc.) immediately below.

To prevent race conditions, there are no global variables in standard components.  
 
