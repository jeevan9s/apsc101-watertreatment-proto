import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { SystemPhaseCard, SystemStatusAndPhase, SystemStatusCard } from "./SystemStatusCard";
import { LogDataCard } from "./LogDataCard";
import { Payload } from "@/lib/frontendHandlers";

export function StatusCards({ payload, turbidityBefore, turbidityAfter, reduction }: {
  payload: Payload;
  turbidityBefore: number;
  turbidityAfter: number;
  reduction: number;
}) {
  return (
    <div className="flex flex-col gap-4 md:w-1/2">
      <div className="flex gap-4">
        <SystemStatusAndPhase payload={payload} />
        <LogDataCard />
      </div> 

      <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl transform transition-transform duration-200 ease-in-out hover:scale-105">
        <CardHeader>
          <CardTitle className="text-xs text-white/70">Inlet Turbidity</CardTitle>
        </CardHeader>
        <CardContent className="text-xl font-semibold text-white py-2">{turbidityBefore} NTU</CardContent>
      </Card>

      <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl transform transition-transform duration-200 ease-in-out hover:scale-105">
        <CardHeader>
          <CardTitle className="text-xs text-white/70">Outlet Turbidity</CardTitle>
        </CardHeader>
        <CardContent className="text-xl font-semibold text-white py-2">{turbidityAfter} NTU</CardContent>
      </Card>

      <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl transform transition-transform duration-200 ease-in-out hover:scale-105">
        <CardHeader>
          <CardTitle className="text-xs text-white/70">Reduction Efficiency</CardTitle>
        </CardHeader>
        <CardContent className="text-xl font-semibold text-white py-2">{reduction.toFixed(1)} %</CardContent>
      </Card>
    </div>
  );
}
