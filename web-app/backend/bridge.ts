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
  fs.writeFileSync(logfile, "timestamp,phase,turbidity_in,turbidity_out,system_status\n");
}

// init serial - shud match Arduino side
const serial = new SerialPort({ path: "COM5", baudRate: 115200 });
const parser = serial.pipe(new ReadlineParser({ delimiter: "\n" }));

function processData(payload: {
  turbidity_in: number;
  turbidity_out: number;
  status: string;
  phase: string;
  ts: number;
}) {
  return {
    turbidity: {
      in: payload.turbidity_in ?? 0,
      out: payload.turbidity_out ?? 0
    },
    system: {
      status: payload.status ?? "offline",
      phase: payload.phase ?? "idle",
    },
    timestamp: payload.ts ?? Date.now()
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
    const rawLine = line.trim();
    const raw = JSON.parse(rawLine);
    const filtered = processData(raw);

    // broadcast to frontend
    io.emit("sensorData", filtered);

    // CSV loggin
    const row = [
      filtered.timestamp,       // unix ms
      filtered.system.phase,
      filtered.turbidity.in,
      filtered.turbidity.out,
      filtered.system.status
].map(String).join(",") + "\n";
    fs.appendFile(logfile, row, (err) => {
       if (err) console.error("CSV write error:", err);
});


  } catch (err) {
    console.error(`[${new Date().toISOString()}] Malformed JSON:`, line);
  }
});


app.get("/", (req: Request, res: Response) => {
  res.json({
    message: "WPTPDI Backend Bridge Server",
    status: "running",
    endpoints: {
      "/": "Server info",
      "/export-csv": "download data log CSV"
    },
    websocket: "Socket.IO on same port for live data"
  });
});

// endpoint for CSV export (call in a handler)
app.get("/export-csv", (req: Request, res: Response) => {
  if (fs.existsSync(logfile)) {
    res.download(logfile, "WPTPDI_data_log.csv");
  } else {
    res.status(404).send("log file not found");
  }
});

server.listen(4000, () => {
  console.log("backend running on http://localhost:4000");
});