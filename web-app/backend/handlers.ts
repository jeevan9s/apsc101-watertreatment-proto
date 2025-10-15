// handlers for extracting fields from JSON payload 
// sys status, turbidity data 
import { useState, useEffect } from "react";
import { Socket  } from "socket.io";


export interface Payload {
    turbidity: {in: number, out: number};
    system: {status: string};
}

export function useSystemData(): Payload {
  const [data, setData] = useState<Payload>({
    turbidity: { in: 0, out: 0 },
    system: { status: "offline" },
  });

  useEffect(() => {
    const socket: Socket = io("http://localhost:4000");

    socket.on("sensorData", (payload: Payload) => {
      setData(payload);
    });

    return () => {
      socket.disconnect();
    };
  }, []);

  return data;
}

export function getSystemStatus(payload: Payload): string {
    return payload.system?.status ?? "offline"
}

export function getTurbidityIn(payload: Payload): number {
    return payload.turbidity?.in ?? 0
}

export function getTurbidityOut(payload: Payload): number {
    return payload.turbidity?.out ?? 0
}

export function getReductionEfficiency(payload: Payload): number {
    const tIn = getTurbidityIn(payload);
    const tOut = getTurbidityOut(payload);
    if (tIn <= 0) return 0;
    const eff = (1 - tOut / tIn) * 100;
    return eff;
}

export function normalizeStatus(status: string): string {
  const normalized = status.toLowerCase();
  const validStatuses = ["offline", "operating", "treated", "online"];
  return validStatuses.includes(normalized) ? normalized : "offline";
}

function io(arg0: string): Socket<import("socket.io").DefaultEventsMap, import("socket.io").DefaultEventsMap, import("socket.io").DefaultEventsMap, any> {
    throw new Error("Function not implemented.");
}
