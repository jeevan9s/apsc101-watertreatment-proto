import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";


// replace w logic to get system status from json payload
const STATUS_STYLES: Record<
  string,
  { color: string; pulse: boolean }
> = {
  online: { color: "text-green-200 bg-green-200", pulse: true },
  operating: { color: "text-slate-400 bg-slate-400", pulse: true },
  offline: { color: "text-neutral-400 bg-neutral-400", pulse: false },
  treated: { color: "text-green-400 bg-green-400", pulse: false },
};

export function SystemStatusCard({ systemStatus }: { systemStatus?: string }) {
  const normalized = (systemStatus || "offline").toLowerCase();
  const style = STATUS_STYLES[normalized] || STATUS_STYLES.offline;

  return (
    <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl flex-1 transform transition-transform duration-200 ease-in-out hover:scale-105">
      <CardHeader>
        <CardTitle className="text-xs text-white/70">System Status</CardTitle>
      </CardHeader>
      <CardContent className="flex items-center justify-between py-2">
        <span className={`text-sm font-medium ${style.color.split(" ")[0]}`}>
          {STATUS_STYLES[normalized] ? systemStatus || "Offline" : "Offline"}
        </span>
        <div
          className={`h-3 w-3 rounded-full ${style.color.split(" ")[1]} ${
            style.pulse ? "animate-pulse" : ""
          }`}
        />
      </CardContent>
    </Card>
  );
}
