import axios from 'axios'
import { Routes, Route } from 'react-router'
import { useState, useEffect } from 'react'
import { HomePage } from './pages/home/HomePage.jsx'
import { CheckoutPage } from './pages/checkout/CheckoutPage.jsx'
import { OrdersPage } from './pages/orders/OrdersPage.jsx'
import { TrackingPage } from './pages/tracking/TrackingPage.jsx'
import { NotFoundPage } from './pages/not-found/NotFoundPage.jsx'
import './App.css'

window.axios = axios;


function App() {
  const [cart, setCart] = useState([]);
  
  const loadCart = async () => 
  {
    const response = await axios.get('/api/cart-items?expand=product');
    setCart(response.data);
  };

  useEffect(() => 
  {
    loadCart(); 
  }, []);

  return (
    <>
      <Routes>
        <Route index element={<HomePage cart={cart} loadCart={loadCart} />} /> {/* index <=> path="/" */}
        <Route path="checkout" element={<CheckoutPage cart={cart} loadCart={loadCart} />} />
        <Route path="orders" element={<OrdersPage cart={cart} loadCart={loadCart} />} />
        <Route path="tracking/:orderId/:productId" element={<TrackingPage cart={cart} />} />
        <Route path="*" element={<NotFoundPage cart={cart} />} />
      </Routes>
    </>
  )
}

export default App
