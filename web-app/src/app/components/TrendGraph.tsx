import { ResponsiveContainer, LineChart, Line, XAxis, YAxis, Tooltip } from 'recharts';

export function TrendGraph({ data }: { data: { name: string; value: number }[] }) {
  return (
    <div className="flex flex-col items-center justify-center h-full w-full">
      <span className="text-2xl font-bold text-slate-400">Trend Graph</span>
      <div className="w-full h-40 flex items-center justify-center">
        {data.length === 0 ? (
          <span className="text-white/40">No data available</span>
        ) : (
          <ResponsiveContainer width="100%" height="100%">
            <LineChart data={data}>
              <XAxis dataKey="name" />
              <YAxis />
              <Tooltip />
              <Line type="monotone" dataKey="value" stroke="#60a5fa" />
            </LineChart>
          </ResponsiveContainer>
        )}
      </div>
    </div>
  );
}
