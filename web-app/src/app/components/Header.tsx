import { motion } from "framer-motion";
import { dmSans } from "../../../fonts";

export function Header() {
  return (
    <motion.header
      initial={{ opacity: 0, y: -20 }}
      animate={{ opacity: 1, y: 0 }}
      transition={{ duration: 0.6, ease: "easeOut" }}
      className="flex flex-col gap-1"
    >
      <h1 className={`text-3xl sm:text-4xl font-semibold tracking-tight ${dmSans.className}`}>
  <span className="text-slate-400">WPTPDI</span>  Monitor
      </h1>
      <p className="text-sm text-white/60">live water treatment insights</p>
    </motion.header>
  );
}
