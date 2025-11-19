# APSC 101 - WPTPDI 
> ( Water Pre-Treatment Plant Digital Interface )


## Overview 
Digital monitoring dashboard for a small-scale water pretreatment plant prototype; supports collection of data (turbidity), system status, and relevant visualizations. 

## Architecture 
Main communication is handled via Serial/UART and Websockets. 
- UI/UX done with Next.js
- Backend done with Node.js.
- Firmware written in Arduino C/C++

<img src="/media/APSC101-final.png" alt="Project Overview" width="400" height="400"/> <img src="/media/WPTPDI-dashboard.png" alt="Dashboard Mockup" width="400" height="400" style="tranform: scale(10)"/> 
## Usage 

to run the web-based dashboard:
```bash
cd web-app
npm run dev

// to start the backend
cd backend
node bridge.js
```

-> the main firmware can be ran via the Arduino IDE. 
