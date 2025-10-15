import React, { type JSX } from "react";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { motion } from "framer-motion";
import { ChevronLeft, ChevronRight } from "lucide-react";

interface CarouselProps {
  carouselItems: { title: string; component: JSX.Element }[];
  carouselIndex: number;
  nextCarousel: () => void;
  prevCarousel: () => void;
}

export function Carousel({ carouselItems, carouselIndex, nextCarousel, prevCarousel }: CarouselProps) {
  return (
    <div className="md:w-1/2 flex flex-col gap-4">
      <motion.div
        key={carouselIndex}
        initial={{ opacity: 0, x: 40 }}
        animate={{ opacity: 1, x: 0 }}
        exit={{ opacity: 0, x: -40 }}
        transition={{ duration: 0.4, ease: "easeInOut" }}
      >
        <Card className="bg-neutral-900 border border-neutral-800 rounded-2xl flex-1 transform transition-transform duration-200 ease-in-out hover:scale-105">
          <CardHeader>
            <CardTitle className="text-sm text-white/70">{carouselItems[carouselIndex].title}</CardTitle>
          </CardHeader>
          <CardContent className="h-80 flex items-center justify-center text-white/40 text-sm">
            {carouselItems[carouselIndex].component}
          </CardContent>
        </Card>
      </motion.div>
      <div className="flex justify-between mt-2">
        <Button
          onClick={prevCarousel}
          className="bg-slate-400 hover:bg-slate-300 cursor-pointer rounded-xl px-4 py-1 text-sm transform transition-transform duration-200 ease-in-out hover:scale-110"
        >
          <ChevronLeft color="#1e293b" />
        </Button>
        <Button
          onClick={nextCarousel}
          className="bg-slate-400 hover:bg-slate-300 rounded-xl px-4 py-1 text-sm transform transition-transform duration-200 ease-in-out hover:scale-110 cursor-pointer"
        >
          <ChevronRight color="#1e293b" />
        </Button>
      </div>
    </div>
  );
}
