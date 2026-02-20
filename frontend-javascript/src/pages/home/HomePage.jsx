import axios from 'axios';
import { useEffect, useState } from 'react';
import { useSearchParams } from 'react-router';
import { Header } from '../../components/Header.jsx';
//import CheckmarkIcon from '../../assets/images/icons/checkmark.png';
import { ProductsGrid } from './ProductsGrid.jsx';
import './HomePage.css'

export function HomePage({ cart, loadCart }) 
{
  const [products, setProducts] = useState([]);
  const [searchParams] = useSearchParams();
  const search = searchParams.get('search');

  useEffect(() => 
  {
    const getHomeData = async () => 
    {
      const searchString = search ? `/api/products?search=${search}` : '/api/products';
      const response = await axios.get(searchString);
      setProducts(response.data);
    };

    getHomeData();
  }, [search]);

  return (
    <>
      <link rel="icon" type="image/svg+xml" href="home-favicon.png" />
      <title>Ecommerce Project</title>

      <Header cart={cart} />

      <div className="home-page">
        <ProductsGrid products={products} loadCart={loadCart} />
      </div>
    </>
  );
}