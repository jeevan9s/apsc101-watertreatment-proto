
import type { Metadata } from "next";
import { inter, dmSans } from '../../fonts';
import "./globals.css";

export const metadata: Metadata = {
  title: "Dashboard" ,
  description: "APSC 101 Project (Team 163)",
    icons: {
    icon: "/favicon.ico",
  },
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  console.log('RootLayout rendered');
  return (
    <html lang="en">
      <head>
        {(() => { console.log('Favicon link tag rendered'); return null; })()}
        <link rel="icon" href="/favicon.ico" />
        <title>Dashboard</title>
      </head>
      <body className={`${inter.className} ${dmSans.className} antialiased`}>
        {children}
      </body>
    </html>
  );
}
