import { useState, useEffect } from "react";
import { ResponsiveContainer, LineChart, Line, XAxis, YAxis, Tooltip } from "recharts";
import { useSystemData, getReductionEfficiency } from "@/lib/frontendHandlers";

interface EfficiencyChartProps {
  maxPoints?: number; // max number of points to show in the chart
}

export function EfficiencyChart({ maxPoints = 20 }: EfficiencyChartProps) {
  const payload = useSystemData();
  const [data, setData] = useState<{ name: string; efficiency: number }[]>([]);

  useEffect(() => {
    const efficiency = getReductionEfficiency(payload);
    const timestamp = new Date().toLocaleTimeString();

    setData(prev => {
      const newData = [...prev, { name: timestamp, efficiency }];
      if (newData.length > maxPoints) newData.shift();
      return newData;
    });
  }, [payload, maxPoints]);

  return (
    <div className="flex flex-col items-center justify-center h-full w-full">
      <span className="text-2xl font-bold text-slate-400">Efficiency Chart</span>
      <div className="w-full h-40 flex items-center justify-center">
        {data.length === 0 ? (
          <span className="text-white/40">no data available</span>
        ) : (
          <ResponsiveContainer width="100%" height="100%">
            <LineChart data={data}>
              <XAxis dataKey="name" />
              <YAxis domain={[0, 100]} tickFormatter={v => `${v}%`} />
              <Tooltip formatter={v => (typeof v === "number" ? `${v.toFixed(1)}%` : v)} />
              <Line type="monotone" dataKey="efficiency" stroke="#60a5fa" />
            </LineChart>
          </ResponsiveContainer>
        )}
      </div>
    </div>
  );
}
