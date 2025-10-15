"use client";
import { useState } from "react";
import { motion } from "framer-motion";
import { Separator } from "@/components/ui/separator";
import { Header } from "./components/Header";
import { StatusCards } from "./components/StatusCards";
import { Carousel } from "./components/Carousel";
import { poppins } from "../../../fonts";
import { TurbidityGauge } from "./components/TurbidityGauge";
import { TrendGraph } from "./components/TrendGraph";
import { EfficiencyChart } from "./components/EfficiencyChart";

const carouselItems = [
  { title: "Inlet Turbidity Gauge", component: <TurbidityGauge label="inlet" /> },
  { title: "Outlet Turbidity Gauge", component: <TurbidityGauge label ="outlet" /> },
  { title: "Turbidity Trend Graph", component: <TrendGraph /> },
  { title: "Efficiency Chart", component: <EfficiencyChart /> },
];

export default function Home() {
  const [systemStatus] = useState("Offline");
  const [carouselIndex, setCarouselIndex] = useState(0);

  const turbidityBefore = 0.0;
  const turbidityAfter = 0.0;
  const reduction = ((turbidityBefore - turbidityAfter) / turbidityBefore) * 100;

  const nextCarousel = () => setCarouselIndex((prev) => (prev + 1) % carouselItems.length);
  const prevCarousel = () => setCarouselIndex((prev) => (prev - 1 + carouselItems.length) % carouselItems.length);

  return (
    <main className={`min-h-screen bg-neutral-950 text-white px-6 py-10 flex flex-col gap-8 ${poppins.className}`}>
      <Header />
      <Separator className="bg-neutral-800" />
      <motion.section
        initial={{ opacity: 0 }}
        animate={{ opacity: 1 }}
        transition={{ delay: 0.2, duration: 0.6 }}
        className="flex flex-col md:flex-row gap-6"
      >
        <StatusCards
          systemStatus={systemStatus}
          turbidityBefore={turbidityBefore}
          turbidityAfter={turbidityAfter}
          reduction={reduction}
        />
        <Carousel
            carouselItems={carouselItems}
            carouselIndex={carouselIndex}
            nextCarousel={nextCarousel}
            prevCarousel={prevCarousel}
          />
      </motion.section>
    </main>
  );
}
