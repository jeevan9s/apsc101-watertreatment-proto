import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Button } from "@/components/ui/button";

export function LogDataCard() {
  return (
    <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl flex-1 transform transition-transform duration-200 ease-in-out hover:scale-105">
      <CardHeader>
        <CardTitle className="text-xs text-white/70">Log Data</CardTitle>
      </CardHeader>
      <CardContent className="flex justify-center py-2">
        <Button className="bg-slate-400 hover:bg-slate-300 text-slate-900 font-semibold rounded-xl px-4 py-1 text-sm transform transition-transform duration-200 ease-in-out hover:scale-110 cursor-pointer">
          export CSV
        </Button>
      </CardContent>
    </Card>
  );
}
