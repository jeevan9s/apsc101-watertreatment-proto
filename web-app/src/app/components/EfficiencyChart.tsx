import { ResponsiveContainer, LineChart, Line, XAxis, YAxis, Tooltip } from 'recharts';

export function EfficiencyChart() {

// got GPT to make some mock data, will replace this after
  const mockData = [
    { name: '10:00', inlet: 3.2, outlet: 0.8 },
    { name: '10:05', inlet: 3.1, outlet: 0.7 },
    { name: '10:10', inlet: 3.0, outlet: 0.6 },
    { name: '10:15', inlet: 2.9, outlet: 0.7 },
    { name: '10:20', inlet: 3.0, outlet: 0.9 },
  ];
  const data = mockData.map(d => ({
    name: d.name,
    efficiency: d.inlet > 0 ? ((1 - d.outlet / d.inlet) * 100) : 0
  }));


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
