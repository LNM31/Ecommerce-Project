![React](https://img.shields.io/badge/React-19.1-61DAFB?logo=react&logoColor=white)
![TypeScript](https://img.shields.io/badge/TypeScript-5.8-3178C6?logo=typescript&logoColor=white)
![Node.js](https://img.shields.io/badge/Node.js-Express-339933?logo=node.js&logoColor=white)
![Vite](https://img.shields.io/badge/Vite-6.3-646CFF?logo=vite&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-Sequelize-003B57?logo=sqlite&logoColor=white)

# Ecommerce Project

A full-stack e-commerce web application with product browsing, cart management, order placement, and package tracking — built with React 19, TypeScript, and Node.js/Express.

---

## Demo

https://github.com/user-attachments/assets/f1ac39dd-6ac0-4f75-8d78-c36afdccce60

---

## Tech Stack

**Frontend:**

| Technology | Purpose |
|------------|---------|
| React 19 | UI framework |
| TypeScript | Type safety |
| Vite | Build tool & dev server |
| React Router 7 | Client-side routing |
| Axios | HTTP client |
| Day.js | Date formatting |
| Vitest + Testing Library | Unit & component testing |

**Backend:**

| Technology | Purpose |
|------------|---------|
| Node.js + Express | REST API server |
| Sequelize | ORM (database abstraction) |
| SQLite (sql.js) | Development database |
| MySQL / PostgreSQL | Production database (optional) |

---

## Prerequisites

Before running this project, make sure you have the following installed:

**Node.js** (v18 or higher) and **npm**:

- **Windows** — Download the installer from [nodejs.org](https://nodejs.org/) (LTS recommended)
- **macOS** — Using Homebrew:
  ```bash
  brew install node
  ```
- **Linux (Ubuntu/Debian)**:
  ```bash
  curl -fsSL https://deb.nodesource.com/setup_lts.x | sudo -E bash -
  sudo apt-get install -y nodejs
  ```

Verify the installation:
```bash
node --version
npm --version
```

**Git** (to clone the repository):

- **Windows** — Download from [git-scm.com](https://git-scm.com/downloads)
- **macOS**:
  ```bash
  brew install git
  ```
- **Linux**:
  ```bash
  sudo apt-get install git
  ```

---

## Getting Started

1. **Clone the repository:**
   ```bash
   git clone https://github.com/LNM31/Ecommerce-Project.git
   cd Ecommerce-Project
   ```

2. **Start the backend** (Terminal 1):
   ```bash
   cd backend
   npm install
   npm run dev
   ```
   The API server will start on `http://localhost:3000`.

3. **Start the frontend** (Terminal 2):
   ```bash
   cd frontend-typescript
   npm install
   npm run dev
   ```
   The app will open on `http://localhost:5173`.

> **Note:** A JavaScript version of the frontend is also available in `frontend-javascript/` — same steps apply.

---

## Project Structure

```
Ecommerce-Project/
├── backend/
│   ├── server.js                  # Express server entry point
│   ├── models/
│   │   ├── index.js               # Sequelize instance & DB config
│   │   ├── Product.js             # Product model
│   │   ├── CartItem.js            # Cart item model
│   │   ├── DeliveryOption.js      # Delivery option model
│   │   └── Order.js               # Order model
│   ├── routes/
│   │   ├── products.js            # GET /api/products
│   │   ├── cartItems.js           # CRUD /api/cart-items
│   │   ├── deliveryOptions.js     # GET /api/delivery-options
│   │   ├── orders.js              # GET/POST /api/orders
│   │   ├── paymentSummary.js      # GET /api/payment-summary
│   │   └── reset.js               # POST /api/reset
│   ├── defaultData/               # Seed data (44 products, delivery options, etc.)
│   └── images/                    # Product images
│
├── frontend-typescript/
│   ├── src/
│   │   ├── App.tsx                # Root component with routing
│   │   ├── components/
│   │   │   └── Header.tsx         # Navigation bar with search & cart badge
│   │   ├── pages/
│   │   │   ├── home/              # Product catalog with responsive grid
│   │   │   ├── checkout/          # Cart, delivery options & payment summary
│   │   │   ├── orders/            # Order history
│   │   │   ├── tracking/          # Package tracking with progress bar
│   │   │   └── not-found/         # 404 page
│   │   └── utils/
│   │       └── money.ts           # Currency formatting utility
│   └── public/                    # Static assets & favicons
│
└── frontend-javascript/           # JavaScript version of the frontend
```

---

## Features

- **Product Catalog** — Browse 44 products with images, ratings, and prices
- **Product Search** — Filter products by name or keywords
- **Shopping Cart** — Add, update quantity, remove items with inline editing
- **Delivery Options** — Choose between Free (7 days), $4.99 (3 days), or $9.99 (1 day) shipping per item
- **Payment Summary** — Real-time cost breakdown with items, shipping, tax (10%), and total
- **Order Placement** — Place orders from cart with automatic tax calculation
- **Order History** — View past orders with product details and "Buy Again" option
- **Package Tracking** — Visual progress bar showing Preparing → Shipped → Delivered status
- **Responsive Design** — Fully responsive layout from mobile to ultrawide (8-column product grid)
- **RESTful API** — Clean Express backend with full CRUD operations
- **Dual Frontend** — Available in both TypeScript and JavaScript

---

## Configuration

The project works out of the box with **zero configuration** for local development. SQLite runs in-memory and persists to a local file automatically.

**Optional** — For production deployment with MySQL or PostgreSQL, set these environment variables on the backend:

```bash
RDS_HOSTNAME=your-database-host
RDS_USERNAME=your-database-user
RDS_PASSWORD=your-database-password
DB_TYPE=mysql    # or "postgres"
PORT=3000        # optional, defaults to 3000
```

