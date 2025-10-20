// main backend 
// run via node 

/*
- read JSON payload frmo firmware/Arduino side
- data filtering, categorizing
- broadcast to frontend w websockets 
- log to CSV and share via HTTP
*/

import { Server } from "socket.io";
import { SerialPort, ReadlineParser } from "serialport";
import fs from "fs"
import http from "http"
import path from "path"
import express, { Request, Response } from "express";

// setup app & websocket
const app = express();
const server = http.createServer(app);
const io = new Server(server, {cors: {origin: "*"}});

// logging support
const logDir = "./logs"
if (!fs.existsSync(logDir)) fs.mkdirSync(logDir);

const logfile = path.join(logDir, "data_log.csv");
if (!fs.existsSync(logfile)) {
  fs.writeFileSync(logfile, "timestamp,turbidity_in,turbidity_out,status\n");
}

// init serial - shud match Arduino side
const serial = new SerialPort({ path: "COM3", baudRate: 9600 });
const parser = serial.pipe(new ReadlineParser({ delimiter: "\n" }));

function processData(raw: { system: { status: string; }; turbidity_in: any; turbidity_out: any; pump_state: any; }) {
  const status = raw.system?.status?.toLowerCase() ? "operating" : "offline";
 
  return {
    turbidity: { in: raw.turbidity_in ?? 0, out: raw.turbidity_out ?? 0 },
    system: { pump: raw.pump_state ?? 0, status },
  };
}

/* 
process json payload in the form:
{
  "turbidity": { "in": 3.2, "out": 1.1 },
  "system": { "status": "operating" }
}
*/

// parse serial data
parser.on("data", (line) => {
  try {
    const raw = JSON.parse(line);
    const filtered = processData(raw);

    io.emit("sensorData", filtered);

    // CSV loggin
    const row = `${Date.now()},${filtered.turbidity.in},${filtered.turbidity.out},${filtered.system.pump},${filtered.system.status}\n`;
    fs.appendFileSync(logfile, row);

  } catch (err) {
    console.error("malformed JSON:", line);
  }
});

// endpoint for CSV export (call in a handler)
app.get("/export-csv", (req: Request, res: Response) => {
  if (fs.existsSync(logfile)) {
    res.download(logfile, "WPTPDI_data_log.csv");
  } else {
    res.status(404).send("log file not found");
  }
});

// start
server.listen(4000, () => {
  console.log("backend running on http://localhost:4000");
});