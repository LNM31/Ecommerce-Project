import { formatMoney } from "../../utils/money";
import axios from "axios";
import './CartItemDetails.css';
import { useState } from "react";

export function CartItemDetails({ cartItem, loadCart }) 
{
  const [isUpdating, setIsUpdating] = useState(false);
  const [quantity, setQuantity] = useState(cartItem.quantity);

  async function updateQuantity()
  {
    if(isUpdating) 
    {
      await axios.put(`/api/cart-items/${cartItem.product.id}`, {
        quantity : Number(quantity)
      });

      await loadCart();
    }
    setIsUpdating(!isUpdating);
  }
  function keyUpdateQuantity(event)
  {
    if(event.key === 'Enter')
    {
      updateQuantity();
    }
    else if(event.key === 'Escape')
    {
      setQuantity(cartItem.quantity);
      setIsUpdating(false);
    }
  }

  const deleteCartItem = async () => 
  {
    await axios.delete(`/api/cart-items/${cartItem.productId}`);
    await loadCart();
  };

  return (
    <>
      <img className="product-image"
        src={cartItem.product.image} />

      <div className="cart-item-details">
        <div className="product-name">
          {cartItem.product.name}
        </div>
        <div className="product-price">
          {formatMoney(cartItem.product.priceCents)}
        </div>
        <div className="product-quantity">
          <span>
            Quantity:
            {isUpdating && (
              <input type="text"
                value={quantity} 
                onChange={event => setQuantity(event.target.value)}
                onKeyDown={keyUpdateQuantity}
                className="quantity-input"
              /> 
            )}
            <span className="quantity-label">{cartItem.quantity}</span>
          </span>
          <span 
            className="update-quantity-link link-primary"
            onClick={updateQuantity}
          >
            Update
          </span>
          <span 
            className="delete-quantity-link link-primary"
            onClick={deleteCartItem}
          >
            Delete
          </span>
        </div>
      </div>
    </>
  );
}