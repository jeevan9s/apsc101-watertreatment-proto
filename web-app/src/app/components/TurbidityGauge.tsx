import { ResponsiveContainer, PieChart, Pie, Cell } from 'recharts';

interface TurbidityGaugeProps {
  label: string;
  value?: number; 
  max?: number;   
}

export function TurbidityGauge({ label, value = 0, max = 10 }: TurbidityGaugeProps) {
  const gaugeData = [
    { name: 'Value', value: Math.min(value, max) },
    { name: 'Remainder', value: Math.max(0, max - value) },
  ];
  const COLORS = ['#94a3b8', '#e5e7eb']; 

  return (
    <div className="flex flex-col items-center justify-center h-full w-full">
      <span className="text-2xl font-bold text-slate-400 mb-8">{label} Turbidity</span>
      <div className="w-full h-40 flex items-center justify-center">
        <ResponsiveContainer width="80%" height="100%">
          <PieChart>
            <Pie
              data={gaugeData}
              startAngle={180}
              endAngle={0}
              innerRadius={50}
              outerRadius={80}
              dataKey="value"
              stroke="none"
            >
              {gaugeData.map((entry, idx) => (
                <Cell key={`cell-${idx}`} fill={COLORS[idx]} />
              ))}
            </Pie>
          </PieChart>
        </ResponsiveContainer>
        <span className="absolute text-2xl font-semibold text-slate-700 mt-2">
          {value}
        </span>
      </div>
    </div>
  );
}
