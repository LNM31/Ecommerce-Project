import { NavLink, useNavigate, useSearchParams } from 'react-router';
import { useState, } from 'react';
import CartIcon from '../assets/images/icons/cart-icon.png';
import SearchIcon from '../assets/images/icons/search-icon.png';
import HomeIconWhite from '../assets/images/home-logo-white.png';
import './Header.css'

type HeaderProps = {
  cart: {
    productId: string;
    quantity: number;
    deliveryOptionId: string;
  }[];
};

export function Header({ cart }: HeaderProps) {
  const navigate = useNavigate();
  const [searchParams] = useSearchParams();
  const searchText = searchParams.get('search');

  const [search, setSearch] = useState(searchText || '');
  

  let totalQuantity = 0;

  cart.forEach((cartItem) => {
    totalQuantity += cartItem.quantity;
  });

  function updateSearchInput(event)
  {
    setSearch(event.target.value);
  }
  function enterSearchProducts(event) 
  {
    if(event.key === 'Enter')
      searchProducts();
  }

  function searchProducts()
  {
    navigate(`/?search=${search}`);
  }

  return (
    <>
      <div className="header">
        <div className="left-section">
          <NavLink to="/" className="header-link home-container"> {/* should use Link(component) instead of a(element), NavLink goes to another page without reloading */}
            <img className="logo home-icon"
              src={HomeIconWhite} />
            <div className="home-text">Home</div>
          </NavLink>
        </div>

        <div className="middle-section">
          <input 
            className="search-bar" 
            type="text" placeholder="Search" 
            value={search}
            onChange={updateSearchInput}
            onKeyDown={enterSearchProducts}
          />

          <button className="search-button"
            onClick={searchProducts}
          >
            <img className="search-icon" src={SearchIcon} />
          </button>
        </div>

        <div className="right-section">
          <NavLink className="orders-link header-link" to="/orders">

            <span className="orders-text">Orders</span>
          </NavLink>

          <NavLink className="cart-link header-link" to="/checkout">
            <img className="cart-icon" src={CartIcon} />
            <div className="cart-quantity">{totalQuantity}</div>
            <div className="cart-text">Cart</div>
          </NavLink>
        </div>
      </div>
    </>
  );
}