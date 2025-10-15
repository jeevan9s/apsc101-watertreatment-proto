# APSC 101 - WPTPDI 
> ( Water Pre-Treatment Plant Digital Interface )


## Overview 
Digital monitoring dashboard for a small-scale water pretreatment plant prototype; supports collection of data (turbidity), system status, and TBD functionality. 

## Architecture 
Main communication is handles via Serial/UART and Websockets. 
- UI/UX done with Next.js
- Firmware written in Arduino C/C++

<img src="/media/APSC_101_WPTPDI_diagram.png" width="50%" height="50%"  />
  

## Usage 

to run the web-based dashboard:
```bash
cd web-app
npm run dev
```

-> the main firmware can be ran via the Arduino IDE. 
