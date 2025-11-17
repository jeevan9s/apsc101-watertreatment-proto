import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { normalizePhase, normalizeStatus, Payload, getCurrentPhase, getSystemStatus } from "@/lib/frontendHandlers";

const STATUS_STYLES: Record<string, { color: string; pulse: boolean }> = {
  online: { color: "text-green-200 bg-green-200", pulse: true },
  treating: { color: "text-slate-400 bg-slate-400", pulse: true },
  offline: { color: "text-neutral-400 bg-neutral-400", pulse: false },
  treated: { color: "text-green-400 bg-green-400", pulse: false },
};

const PHASE_STYLES: Record<string, { color: string; pulse: boolean }> = {
  idle: { color: "text-orange-300 bg-orange-300", pulse: true },
  "coagulant dispensing": { color: "text-cyan-700 bg-cyan-700", pulse: true },
  "fast mixing": { color: "text-blue-500 bg-blue-500", pulse: true },
  "slow mixing": { color: "text-purple-500 bg-purple-500", pulse: true },
  "filter pressing": { color: "text-yellow-400 bg-yellow-400", pulse: true },
  treated: { color: "text-green-400 bg-green-400", pulse: false },
  offline: { color: "text-neutral-400 bg-neutral-400", pulse: false },
};

export function SystemStatusCard({ payload }: { payload?: Payload }) {
  const status = normalizeStatus(getSystemStatus(payload));
  const statusStyle = STATUS_STYLES[status] || STATUS_STYLES.offline;

  return (
    <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl flex-1 transform transition-transform duration-200 ease-in-out hover:scale-105">
      <CardHeader>
        <CardTitle className="text-xs text-white/70">System Status</CardTitle>
      </CardHeader>
      <CardContent className="flex items-center justify-between py-2">
        <span className={`text-sm font-medium ${statusStyle.color.split(" ")[0]}`}>
          {status}
        </span>
        <div
          className={`h-3 w-3 rounded-full ${statusStyle.color.split(" ")[1]} ${
            statusStyle.pulse ? "animate-pulse" : ""
          }`}
        />
      </CardContent>
    </Card>
  );
}

export function SystemPhaseCard({ payload }: { payload?: Payload }) {
  const phase = normalizePhase(getCurrentPhase(payload));
  const phaseStyle = PHASE_STYLES[phase] || PHASE_STYLES.offline;

  return (
    <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl flex-1 transform transition-transform duration-200 ease-in-out hover:scale-105 ml-2">
      <CardHeader>
        <CardTitle className="text-xs text-white/70">System Phase</CardTitle>
      </CardHeader>
      <CardContent className="flex items-center justify-between py-2">
        <span className={`text-sm font-medium ${phaseStyle.color.split(" ")[0]}`}>
          {phase}
        </span>
        <div
          className={`h-3 w-3 rounded-full ${phaseStyle.color.split(" ")[1]} ${
            phaseStyle.pulse ? "animate-pulse" : ""
          }`}
        />
      </CardContent>
    </Card>
  );
}

export function SystemStatusAndPhase({ payload }: { payload?: Payload }) {
  return (
    <div className="flex w-full space-x-2">
      <SystemStatusCard payload={payload} />
      <SystemPhaseCard payload={payload} />
    </div>
  );
}
