"use strict";
// main backend 
// run via node 
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
/*
- read JSON payload frmo firmware/Arduino side
- data filtering, categorizing
- broadcast to frontend w websockets
- log to CSV and share via HTTP
*/
const socket_io_1 = require("socket.io");
const serialport_1 = require("serialport");
const fs_1 = __importDefault(require("fs"));
const http_1 = __importDefault(require("http"));
const path_1 = __importDefault(require("path"));
const express_1 = __importDefault(require("express"));
// setup app & websocket
const app = (0, express_1.default)();
const server = http_1.default.createServer(app);
const io = new socket_io_1.Server(server, { cors: { origin: "*" } });
// logging support
const logDir = "./logs";
if (!fs_1.default.existsSync(logDir))
    fs_1.default.mkdirSync(logDir);
const logfile = path_1.default.join(logDir, "data_log.csv");
if (!fs_1.default.existsSync(logfile)) {
    fs_1.default.writeFileSync(logfile, "timestamp,turbidity_in,turbidity_out,status\n");
}
// init serial - shud match Arduino side
const serial = new serialport_1.SerialPort({ path: "COM5", baudRate: 9600 });
const parser = serial.pipe(new serialport_1.ReadlineParser({ delimiter: "\n" }));

serial.on('open', () => {
    console.log('Serial port opened successfully on COM5');
});

serial.on('error', (err) => {
    console.error('Serial port error:', err.message);
});

serial.on('close', () => {
    console.log('Serial port closed');
});

parser.on('data', (data) => {
    console.log('Raw serial data received:', data);
});
function processData(raw) {
    var _a, _b, _c, _d;
    const status = ((_a = raw.status) === null || _a === void 0 ? void 0 : _a.toLowerCase()) || "offline";
    return {
        turbidity: { in: (_b = raw.turbidity_in) !== null && _b !== void 0 ? _b : 0, out: (_c = raw.turbidity_out) !== null && _c !== void 0 ? _c : 0 },
        system: { pump: (_d = raw.pump) !== null && _d !== void 0 ? _d : 0, status },
    };
}
/*
process json payload in the form:
{
  "turbidity": { "in": 3.2, "out": 1.1 },
  "system": { "status": "operating" }
}
*/
// buffer for incomplete JSON data
let jsonBuffer = "";

// parse serial data
parser.on("data", (line) => {
    console.log('Processing line:', line); // Debug log
    try {
        // Clean the line and add to buffer
        const cleanLine = line.trim();
        console.log('Clean line:', cleanLine); // Debug log
        jsonBuffer += cleanLine;
        
        // Try to find complete JSON objects
        let startIndex = 0;
        while (true) {
            const openBrace = jsonBuffer.indexOf("{", startIndex);
            if (openBrace === -1) break;
            
            const closeBrace = jsonBuffer.indexOf("}", openBrace);
            if (closeBrace === -1) break;
            
            const jsonStr = jsonBuffer.substring(openBrace, closeBrace + 1);
            console.log('Attempting to parse JSON:', jsonStr); // Debug log
            
            try {
                const raw = JSON.parse(jsonStr);
                console.log('Successfully parsed JSON:', raw); // Debug log
                const filtered = processData(raw);
                io.emit("sensorData", filtered);
                console.log('Emitted data:', filtered); // Debug log
                // CSV logging
                const row = `${Date.now()},${filtered.turbidity.in},${filtered.turbidity.out},${filtered.system.pump},${filtered.system.status}\n`;
                fs_1.default.appendFileSync(logfile, row);
                
                // Remove processed JSON from buffer
                jsonBuffer = jsonBuffer.substring(closeBrace + 1);
                startIndex = 0;
            } catch (parseError) {
                console.log('JSON parse error:', parseError.message); // Debug log
                // If JSON is malformed, try next potential start
                startIndex = openBrace + 1;
            }
        }
        
        // Keep buffer size reasonable
        if (jsonBuffer.length > 1000) {
            jsonBuffer = jsonBuffer.substring(500);
        }
        
    } catch (err) {
        console.error("Serial data error:", err.message);
    }
});
app.get("/", (req, res) => {
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
app.get("/export-csv", (req, res) => {
    if (fs_1.default.existsSync(logfile)) {
        res.download(logfile, "WPTPDI_data_log.csv");
    }
    else {
        res.status(404).send("log file not found");
    }
});
// start
server.listen(4000, () => {
    console.log("backend running on http://localhost:4000");
});
