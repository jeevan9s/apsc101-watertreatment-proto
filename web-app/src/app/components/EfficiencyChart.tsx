import { ResponsiveContainer, LineChart, Line, XAxis, YAxis, Tooltip } from 'recharts';

export function EfficiencyChart({ data }: { data: { name: string; efficiency: number }[] }) {
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
              <Tooltip formatter={v => (typeof v === 'number' ? `${v.toFixed(1)}%` : v)} />
              <Line type="monotone" dataKey="efficiency" stroke="#60a5fa" />
            </LineChart>
          </ResponsiveContainer>
        )}
      </div>
    </div>
  );
}
