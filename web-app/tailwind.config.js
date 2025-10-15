/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./src/**/*.{js,ts,jsx,tsx}",
    "./app/**/*.{js,ts,jsx,tsx}"
  ],
  theme: {
    extend: {
      fontFamily: {
        sans: [
          'var(--font-geist-sans)',
          'Maven Pro',
          'ui-sans-serif',
          'system-ui',
          'sans-serif'
        ],
        dm: [
          'DM Sans',
          'ui-sans-serif',
          'system-ui',
          'sans-serif'
        ],
        geist: [
          'var(--font-geist-sans)',
          'ui-sans-serif',
          'system-ui',
          'sans-serif'
        ],
        'geist-mono': [
          'var(--font-geist-mono)',
          'ui-monospace',
          'SFMono-Regular',
          'monospace'
        ]
      }
    }
  },
  plugins: [],
};
