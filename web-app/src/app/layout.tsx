
import type { Metadata } from "next";
import { inter, dmSans } from '../../../fonts';
import "./globals.css";

export const metadata: Metadata = {
  title: "Dashboard" ,
  description: "APSC 101 Project (Team 163)",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <head>
        <title>Dashboard</title>
      </head>
      <body className={`${inter.className} ${dmSans.className} antialiased`}>
        {children}
      </body>
    </html>
  );
}
