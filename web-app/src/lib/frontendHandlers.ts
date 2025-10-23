import { useState, useEffect } from "react";
import io from "socket.io-client";

export interface Payload {
  turbidity: { in: number; out: number };
  system: { status: string; pump: number };
}

export function useSystemData() {
  const [data, setData] = useState<Payload>({
    turbidity: { in: 0, out: 0 },
    system: { status: "offline", pump: 0 },
  });

  useEffect(() => {
    if (typeof window === "undefined") return;
    console.log("DEBUG - Connecting to socket...");
    const socket = io("http://localhost:4000");
    
    socket.on("sensorData", (payload: Payload) => {
      console.log("received payload:", payload);
      setData(payload);
    });
    
    return () => {
      socket.disconnect();
    };
  }, []);

  return data;
}

export function getSystemStatus(payload: Payload): string {
  return payload.system?.status ?? "offline";
}

export function getTurbidityIn(payload: Payload): number {
  return payload.turbidity?.in ?? 0;
}

export function getTurbidityOut(payload: Payload): number {
  return payload.turbidity?.out ?? 0;
}

export function getPumpState(payload: Payload): number {
  return payload.system?.pump ?? 0;
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
  const validStatuses = ["offline", "treating", "monitoring", "clean", "alert"];
  return validStatuses.includes(normalized) ? normalized : "offline";
}
