// handlers for extracting fields from JSON payload 
// sys status, turbidity & liquidDetected data
import { useState, useEffect } from "react";
import io from "socket.io-client";
import type { Socket } from "socket.io-client";

export interface Payload {
  turbidity: { in: number; out: number };
  status: string;
  timestamp: number;
}

export function useSystemData(): Payload {
  const [data, setData] = useState<Payload>({
    turbidity: { in: 0, out: 0 },
    status: "offline",
    timestamp: 0,
  });

  useEffect(() => {
    const socket = io("http://localhost:4000");

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
  return payload.status ?? "offline";
}

export function getTurbidityIn(payload: Payload): number {
  return payload.turbidity?.in ?? 0;
}

export function getTurbidityOut(payload: Payload): number {
  return payload.turbidity?.out ?? 0;
}

export function getReductionEfficiency(payload: Payload): number {
  const tIn = getTurbidityIn(payload);
  const tOut = getTurbidityOut(payload);
  if (tIn <= 0) return 0;
  return (1 - tOut / tIn) * 100;
}

export function getTimestamp(payload: Payload): number {
  return payload.timestamp ?? Date.now();
}

export function normalizeStatus(status: string): string {
  const normalized = status.toLowerCase();
  const validStatuses = ["offline", "treating", "treated", "alert"];
  return validStatuses.includes(normalized) ? normalized : "offline";
}
